"""Announce a solved problem in a Discord forum channel (run by the post-commit hook)."""

import json
import re
import urllib.error
import urllib.request
from pathlib import Path

CONFIG = Path.home() / ".config" / "solve" / "discord.json"
API = "https://discord.com/api/v10"
LIMIT = 2000  # Discord's message length cap

# leading header comment + import block, and the `if __name__` harness at the bottom
PREAMBLE_RE = re.compile(r"^(?:(?:#.*|import .*|from .*|)\n)*")
HARNESS_RE = re.compile(r"^if __name__ == .__main__.:\n.*", re.M | re.S)


def solution_body(text: str) -> str:
    """solve.py minus the header, imports and harness: what a human would paste."""
    return HARNESS_RE.sub("", PREAMBLE_RE.sub("", text, count=1)).strip()


def code_message(code: str) -> str:
    fence = "```py\n{}\n```"
    if len(fence.format(code)) > LIMIT:
        tail = "\n# … truncated"
        code = code[: LIMIT - len(fence.format("")) - len(tail)] + tail
    return fence.format(code)


def load_config(path: Path = CONFIG) -> dict | None:
    """{"token": ..., "channels": {"Easy": <forum id>, ...}} or None if the file doesn't exist."""
    if not path.exists():
        return None
    config = json.loads(path.read_text())
    for key in ("token", "channels"):
        if key not in config:
            raise ValueError(f"{path}: missing '{key}'")
    return config


class Api:
    """`api(method, path, body)` against the Discord REST API as a bot; returns the parsed JSON reply."""

    def __init__(self, token: str):
        self.headers = {
            "Authorization": f"Bot {token}",
            "Content-Type": "application/json",
            "User-Agent": "DiscordBot (https://github.com/fuad-daoud/py-solve, 1.0)",
        }

    def __call__(self, method: str, path: str, body: dict | None = None):
        data = json.dumps(body).encode() if body is not None else None
        req = urllib.request.Request(API + path, data, self.headers, method=method)
        try:
            with urllib.request.urlopen(req, timeout=20) as resp:
                raw = resp.read()
        except urllib.error.HTTPError as e:
            raise RuntimeError(f"{method} {path}: {e.code} {e.read().decode(errors='replace')}") from e
        except urllib.error.URLError as e:
            raise RuntimeError(f"{method} {path}: {e.reason}") from e
        return json.loads(raw) if raw else None


def find_thread(api, forum: dict, title: str) -> dict | None:
    """The forum post named `title` (case-insensitive): active threads first, then the newest 100 archived."""
    wanted = title.strip().casefold()

    def match(threads):
        return next((t for t in threads if t["name"].strip().casefold() == wanted), None)

    active = api("GET", f"/guilds/{forum['guild_id']}/threads/active")["threads"]
    if found := match(t for t in active if t.get("parent_id") == forum["id"]):
        return found
    return match(api("GET", f"/channels/{forum['id']}/threads/archived/public?limit=100")["threads"])


def tag_ids(forum: dict, *names: str) -> list[str]:
    return [t["id"] for t in forum["available_tags"] if t["name"] in names]


def create_post(api, forum: dict, meta, tag: str) -> dict:
    return api("POST", f"/channels/{forum['id']}/threads", {
        "name": meta.title, "applied_tags": tag_ids(forum, tag), "message": {"content": meta.url},
    })


def mark_solved(api, forum: dict, thread: dict) -> None:
    """Swap In Progress / Not Solved for Solved on `thread`, keeping unrelated tags (e.g. SQL)."""
    solved = tag_ids(forum, "Solved")
    stale = set(tag_ids(forum, "In Progress", "Not Solved"))
    current = thread.get("applied_tags", [])
    wanted = [t for t in current if t not in stale] + [t for t in solved if t not in current]
    if wanted != current:
        api("PATCH", f"/channels/{thread['id']}", {"applied_tags": wanted})


def _forum(meta, config: dict, api) -> dict | None:
    channel = config["channels"].get(meta.difficulty)
    return api("GET", f"/channels/{channel}") if channel else None


def start_post(meta, config: dict, api) -> str:
    """`make start`: open the problem's forum post tagged In Progress, unless one already exists."""
    forum = _forum(meta, config, api)
    if forum is None:
        return f"no channel configured for {meta.difficulty}; skipped"
    if find_thread(api, forum, meta.title):
        return f"{meta.title} already posted in #{forum['name']}"
    create_post(api, forum, meta, "In Progress")
    return f"posted {meta.title} as In Progress in #{forum['name']}"


def announce(meta, code: str, config: dict, api) -> str:
    """Post `code` for `meta` in the forum for its difficulty: a new post, or a reply if one exists."""
    forum = _forum(meta, config, api)
    if forum is None:
        return f"no channel configured for {meta.difficulty}; skipped"
    message = code_message(code)
    thread = find_thread(api, forum, meta.title)
    if thread is None:
        thread = create_post(api, forum, meta, "Solved")
        api("POST", f"/channels/{thread['id']}/messages", {"content": message})
        return f"posted {meta.title} in #{forum['name']}"
    mark_solved(api, forum, thread)
    if any(m["content"] == message for m in api("GET", f"/channels/{thread['id']}/messages?limit=100")):
        return f"{meta.title} already posted in #{forum['name']}; nothing new"
    api("POST", f"/channels/{thread['id']}/messages", {"content": message})
    return f"replied in existing post {meta.title} in #{forum['name']}"
