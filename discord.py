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


def announce(meta, code: str, config: dict, api) -> str:
    """Post `code` for `meta` in the forum for its difficulty: a new post, or a reply if one exists."""
    channel = config["channels"].get(meta.difficulty)
    if not channel:
        return f"no channel configured for {meta.difficulty}; skipped"
    forum = api("GET", f"/channels/{channel}")
    message = code_message(code)
    thread = find_thread(api, forum, meta.title)
    if thread is None:
        tags = [t["id"] for t in forum["available_tags"] if t["name"] == "Solved"]
        thread = api("POST", f"/channels/{forum['id']}/threads", {
            "name": meta.title, "applied_tags": tags, "message": {"content": meta.url},
        })
        api("POST", f"/channels/{thread['id']}/messages", {"content": message})
        return f"posted {meta.title} in #{forum['name']}"
    if any(m["content"] == message for m in api("GET", f"/channels/{thread['id']}/messages?limit=100")):
        return f"{meta.title} already posted in #{forum['name']}; nothing new"
    api("POST", f"/channels/{thread['id']}/messages", {"content": message})
    return f"replied in existing post {meta.title} in #{forum['name']}"
