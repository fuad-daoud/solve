import lc
import discord

SOLVE = """# 1. Two Sum [Easy]
# https://leetcode.com/problems/two-sum/
import bisect
from collections import *
from typing import *


class Solution:
    def twoSum(self, nums: list[int], target: int) -> list[int]:
        return [0, 1]


if __name__ == "__main__":
    import lc

    lc.test(Solution)
"""


def test_solution_body_keeps_only_the_solution():
    assert discord.solution_body(SOLVE) == (
        "class Solution:\n"
        "    def twoSum(self, nums: list[int], target: int) -> list[int]:\n"
        "        return [0, 1]"
    )


def test_solution_body_keeps_helper_classes_and_works_without_harness():
    text = "# 1. X [Easy]\n# https://leetcode.com/problems/x/\nfrom typing import *\n\nclass Node:\n    pass\n\n\nclass Solution:\n    pass\n"
    assert discord.solution_body(text) == "class Node:\n    pass\n\n\nclass Solution:\n    pass"


def test_load_config_returns_none_when_missing(tmp_path):
    assert discord.load_config(tmp_path / "discord.json") is None


def test_load_config_reads_token_and_channels(tmp_path):
    path = tmp_path / "discord.json"
    path.write_text('{"token": "abc", "channels": {"Easy": "1", "Medium": "2"}}')
    assert discord.load_config(path) == {"token": "abc", "channels": {"Easy": "1", "Medium": "2"}}


def test_load_config_rejects_incomplete_file(tmp_path):
    path = tmp_path / "discord.json"
    path.write_text('{"token": "abc"}')
    try:
        discord.load_config(path)
    except ValueError as e:
        assert "channels" in str(e)
    else:
        raise AssertionError("expected ValueError")


META = lc.Meta(1, "Two Sum", "Easy", "two-sum")
CONFIG = {"token": "t", "channels": {"Easy": "100"}}
FORUM = {"id": "100", "name": "easy-problems", "guild_id": "900",
         "available_tags": [{"id": "t1", "name": "Not Solved"}, {"id": "t2", "name": "Solved"}]}
CODE = "class Solution:\n    pass"
CODE_MESSAGE = "```py\nclass Solution:\n    pass\n```"


class FakeApi:
    """Canned responses keyed by (method, path); records every call."""

    def __init__(self, responses):
        self.responses = responses
        self.calls = []

    def __call__(self, method, path, body=None):
        self.calls.append((method, path, body))
        return self.responses[(method, path)]


def test_announce_creates_a_post_with_url_then_code():
    api = FakeApi({
        ("GET", "/channels/100"): FORUM,
        ("GET", "/guilds/900/threads/active"): {"threads": []},
        ("GET", "/channels/100/threads/archived/public?limit=100"): {"threads": [], "has_more": False},
        ("POST", "/channels/100/threads"): {"id": "555"},
        ("POST", "/channels/555/messages"): {"id": "556"},
    })
    result = discord.announce(META, CODE, CONFIG, api)
    assert ("POST", "/channels/100/threads", {
        "name": "Two Sum", "applied_tags": ["t2"],
        "message": {"content": "https://leetcode.com/problems/two-sum/"},
    }) in api.calls
    assert api.calls[-1] == ("POST", "/channels/555/messages", {"content": CODE_MESSAGE})
    assert result == "posted Two Sum in #easy-problems"


def test_announce_replies_in_an_existing_post():
    api = FakeApi({
        ("GET", "/channels/100"): FORUM,
        ("GET", "/guilds/900/threads/active"): {"threads": [
            {"id": "1", "name": "Two Sum", "parent_id": "999"},  # same title, different forum
            {"id": "2", "name": "two sum ", "parent_id": "100"},
        ]},
        ("GET", "/channels/2/messages?limit=100"): [{"content": "https://leetcode.com/problems/two-sum/"}],
        ("PATCH", "/channels/2"): {"id": "2"},
        ("POST", "/channels/2/messages"): {"id": "3"},
    })
    result = discord.announce(META, CODE, CONFIG, api)
    assert [c for c in api.calls if c[0] == "POST"] == [("POST", "/channels/2/messages", {"content": CODE_MESSAGE})]
    assert ("PATCH", "/channels/2", {"applied_tags": ["t2"]}) in api.calls  # a friend's untagged post gets Solved
    assert result == "replied in existing post Two Sum in #easy-problems"


def test_announce_finds_archived_posts():
    api = FakeApi({
        ("GET", "/channels/100"): FORUM,
        ("GET", "/guilds/900/threads/active"): {"threads": []},
        ("GET", "/channels/100/threads/archived/public?limit=100"): {
            "threads": [{"id": "7", "name": "Two Sum", "parent_id": "100"}], "has_more": False},
        ("GET", "/channels/7/messages?limit=100"): [],
        ("PATCH", "/channels/7"): {"id": "7"},
        ("POST", "/channels/7/messages"): {"id": "8"},
    })
    discord.announce(META, CODE, CONFIG, api)
    assert api.calls[-1] == ("POST", "/channels/7/messages", {"content": CODE_MESSAGE})


def test_announce_skips_when_the_same_code_is_already_there():
    api = FakeApi({
        ("GET", "/channels/100"): FORUM,
        ("GET", "/guilds/900/threads/active"): {"threads": [{"id": "2", "name": "Two Sum", "parent_id": "100", "applied_tags": ["t2"]}]},
        ("GET", "/channels/2/messages?limit=100"): [{"content": CODE_MESSAGE}, {"content": "https://leetcode.com/problems/two-sum/"}],
    })
    result = discord.announce(META, CODE, CONFIG, api)
    assert not [c for c in api.calls if c[0] == "POST"]
    assert result == "Two Sum already posted in #easy-problems; nothing new"


def test_announce_skips_difficulties_without_a_channel():
    api = FakeApi({})
    result = discord.announce(lc.Meta(4, "Median", "Hard", "median"), CODE, CONFIG, api)
    assert api.calls == []
    assert result == "no channel configured for Hard; skipped"


class FakeResponse:
    def __init__(self, body):
        self.body = body

    def read(self):
        return self.body

    def __enter__(self):
        return self

    def __exit__(self, *a):
        pass


def test_api_sends_bot_auth_json_and_parses_reply(monkeypatch):
    seen = []

    def urlopen(req, timeout):
        seen.append(req)
        return FakeResponse(b'{"id": "1"}')

    monkeypatch.setattr(discord.urllib.request, "urlopen", urlopen)
    assert discord.Api("tok")("POST", "/channels/1/threads", {"name": "x"}) == {"id": "1"}
    req = seen[0]
    assert req.full_url == "https://discord.com/api/v10/channels/1/threads"
    assert req.get_method() == "POST"
    assert req.get_header("Authorization") == "Bot tok"
    assert req.get_header("Content-type") == "application/json"
    assert req.data == b'{"name": "x"}'


def test_api_get_has_no_body_and_204_is_empty(monkeypatch):
    seen = []

    def urlopen(req, timeout):
        seen.append(req)
        return FakeResponse(b"")

    monkeypatch.setattr(discord.urllib.request, "urlopen", urlopen)
    assert discord.Api("tok")("GET", "/channels/1") is None
    assert seen[0].get_method() == "GET"
    assert seen[0].data is None


def test_api_turns_http_errors_into_readable_messages(monkeypatch):
    import io
    import urllib.error

    def urlopen(req, timeout):
        raise urllib.error.HTTPError(req.full_url, 403, "Forbidden", {}, io.BytesIO(b'{"message": "Missing Access"}'))

    monkeypatch.setattr(discord.urllib.request, "urlopen", urlopen)
    try:
        discord.Api("tok")("GET", "/channels/1")
    except RuntimeError as e:
        assert str(e) == 'GET /channels/1: 403 {"message": "Missing Access"}'
    else:
        raise AssertionError("expected RuntimeError")


def test_code_message_fits_discords_2000_char_limit():
    msg = discord.code_message("x" * 5000)
    assert len(msg) <= 2000
    assert msg.startswith("```py\nxxx")
    assert msg.endswith("\n# … truncated\n```")


FORUM_TAGS = {"available_tags": [
    {"id": "t1", "name": "Not Solved"}, {"id": "t2", "name": "Solved"},
    {"id": "t3", "name": "In Progress"}, {"id": "t4", "name": "SQL"},
]}


def test_start_post_creates_an_in_progress_post():
    api = FakeApi({
        ("GET", "/channels/100"): FORUM | FORUM_TAGS,
        ("GET", "/guilds/900/threads/active"): {"threads": []},
        ("GET", "/channels/100/threads/archived/public?limit=100"): {"threads": [], "has_more": False},
        ("POST", "/channels/100/threads"): {"id": "555"},
    })
    result = discord.start_post(META, CONFIG, api)
    assert api.calls[-1] == ("POST", "/channels/100/threads", {
        "name": "Two Sum", "applied_tags": ["t3"],
        "message": {"content": "https://leetcode.com/problems/two-sum/"},
    })
    assert result == "posted Two Sum as In Progress in #easy-problems"


def test_start_post_leaves_an_existing_post_alone():
    api = FakeApi({
        ("GET", "/channels/100"): FORUM | FORUM_TAGS,
        ("GET", "/guilds/900/threads/active"): {"threads": [{"id": "2", "name": "Two Sum", "parent_id": "100", "applied_tags": ["t2"]}]},
    })
    result = discord.start_post(META, CONFIG, api)
    assert not [c for c in api.calls if c[0] != "GET"]
    assert result == "Two Sum already posted in #easy-problems"


def test_start_post_skips_difficulties_without_a_channel():
    api = FakeApi({})
    assert discord.start_post(lc.Meta(4, "Median", "Hard", "median"), CONFIG, api) == "no channel configured for Hard; skipped"
    assert api.calls == []


def _existing(tags):
    return FakeApi({
        ("GET", "/channels/100"): FORUM | FORUM_TAGS,
        ("GET", "/guilds/900/threads/active"): {"threads": [{"id": "2", "name": "Two Sum", "parent_id": "100", "applied_tags": tags}]},
        ("GET", "/channels/2/messages?limit=100"): [{"content": CODE_MESSAGE}],
        ("PATCH", "/channels/2"): {"id": "2"},
    })


def test_announce_flips_in_progress_to_solved_even_when_code_is_already_there():
    api = _existing(["t3"])
    result = discord.announce(META, CODE, CONFIG, api)
    assert ("PATCH", "/channels/2", {"applied_tags": ["t2"]}) in api.calls
    assert result == "Two Sum already posted in #easy-problems; nothing new"


def test_announce_replaces_not_solved_but_keeps_unrelated_tags():
    api = _existing(["t4", "t1"])
    discord.announce(META, CODE, CONFIG, api)
    assert ("PATCH", "/channels/2", {"applied_tags": ["t4", "t2"]}) in api.calls


def test_announce_does_not_retag_a_post_already_marked_solved():
    api = _existing(["t2", "t4"])
    discord.announce(META, CODE, CONFIG, api)
    assert not [c for c in api.calls if c[0] == "PATCH"]
