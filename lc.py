#!/usr/bin/env python3
"""LeetCode workbench: fetch a problem into solve.py, run cases.txt against it, save solutions."""

import argparse
import html
import importlib.util
import inspect
import json
import re
import shutil
import subprocess
import sys
import time
import traceback
import urllib.error
import urllib.request
from collections import Counter
from dataclasses import dataclass, field
from datetime import date
from html.parser import HTMLParser
from pathlib import Path


@dataclass
class Case:
    inputs: list[str] = field(default_factory=list)
    expected: str | None = None
    unordered: bool = False


def parse_cases(text: str) -> list[Case]:
    """cases.txt: one JSON arg per line, `=> expected` (optional, `~` = any order), blank line between cases."""
    cases: list[Case] = []
    current: Case | None = None
    for raw in text.splitlines():
        line = raw.strip()
        if not line or line.startswith("#"):
            if current and current.inputs:
                cases.append(current)
            current = None
            continue
        if current is None:
            current = Case()
        if line.startswith("=>"):
            expected = line[2:].strip()
            if expected.startswith("~"):
                current.unordered = True
                expected = expected[1:].strip()
            current.expected = expected
        else:
            current.inputs.append(line)
    if current and current.inputs:
        cases.append(current)
    return cases


def _normalize(value, unordered: bool):
    if isinstance(value, float):
        return round(value, 5)
    if isinstance(value, list):
        items = [_normalize(v, unordered) for v in value]
        return sorted(items, key=json.dumps) if unordered else items
    return value


def matches(expected: str, actual, unordered: bool = False) -> bool:
    """Compare LeetCode-style: parsed JSON, floats to 1e-5, optionally order-insensitive lists."""
    try:
        exp = json.loads(expected)
    except json.JSONDecodeError:
        return False
    return _normalize(exp, unordered) == _normalize(actual, unordered)


def find_method(cls):
    """The one public method on a Solution class is the entry point."""
    names = [n for n, v in vars(cls).items() if callable(v) and not n.startswith("_")]
    if len(names) != 1:
        raise ValueError(f"expected exactly one public method on {cls.__name__}, found {names}")
    return getattr(cls, names[0])


@dataclass
class Result:
    case: Case
    status: str  # pass | fail | unchecked | error
    actual: str


def design_ops(case: Case) -> tuple[list[str], list[list]] | None:
    """A design-problem case is two lines, `["MinStack","push",...]` and `[[],[-2],...]`; else None."""
    if len(case.inputs) != 2:
        return None
    try:
        ops, args = (json.loads(a) for a in case.inputs)
    except json.JSONDecodeError:
        return None
    if (isinstance(ops, list) and ops and all(isinstance(o, str) for o in ops)
            and isinstance(args, list) and len(args) == len(ops) and all(isinstance(a, list) for a in args)
            and re.fullmatch(r"[A-Z]\w*", ops[0])):
        return ops, args
    return None


def replay(cls, ops: list[str], args: list[list]) -> list:
    """Construct `cls` with the first args, call each op in turn; LeetCode's output list (None for the constructor)."""
    obj = cls(*args[0])
    return [None] + [getattr(obj, op)(*a) for op, a in zip(ops[1:], args[1:])]


class ListNode:
    """LeetCode's singly-linked list node; solve.py imports it when the snippet uses it."""

    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class TreeNode:
    """LeetCode's binary tree node; solve.py imports it when the snippet uses it."""

    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


def build_list(values: list, pos: int = -1) -> ListNode | None:
    """[1,2,3] → 1→2→3; `pos` ≥ 0 links the tail back to that node (LeetCode's cycle input)."""
    nodes = [ListNode(v) for v in values]
    for a, b in zip(nodes, nodes[1:]):
        a.next = b
    if nodes and 0 <= pos < len(nodes):
        nodes[-1].next = nodes[pos]
    return nodes[0] if nodes else None


def list_values(head) -> list:
    values, seen = [], set()
    while head:
        if id(head) in seen:
            raise ValueError("the returned linked list has a cycle")
        seen.add(id(head))
        values.append(head.val)
        head = head.next
    return values


def build_tree(values: list) -> TreeNode | None:
    """LeetCode's level order, null = no child: [3,9,20,null,null,15,7]."""
    if not values or values[0] is None:
        return None
    root = TreeNode(values[0])
    queue, i = [root], 1
    for node in queue:  # the list grows as we go
        for side in ("left", "right"):
            if i < len(values) and values[i] is not None:
                child = TreeNode(values[i])
                setattr(node, side, child)
                queue.append(child)
            i += 1
        if i >= len(values):
            break
    return root


def tree_values(root) -> list:
    values, queue = [], [root]
    for node in queue:
        values.append(None if node is None else node.val)
        if node is not None:
            queue += [node.left, node.right]
    while values and values[-1] is None:
        values.pop()
    return values


def _node_kind(annotation) -> tuple[str, bool] | None:
    """("ListNode" | "TreeNode", is-a-list-of-them) from an annotation, a string or an object; else None."""
    text = annotation if isinstance(annotation, str) else str(annotation)
    m = re.search(r"\b(ListNode|TreeNode)\b", text)
    return (m.group(1), bool(re.match(r"(typing\.)?[Ll]ist\[", text))) if m else None


def _find(root, val):
    """The node holding `val` in the tree under `root`, or None."""
    queue = [root]
    for node in queue:
        if node is not None:
            if node.val == val:
                return node
            queue += [node.left, node.right]
    return None


def node_args(method, args: list) -> tuple[list, bool]:
    """Turn JSON args into the ListNode / TreeNode params `method` is annotated with.

    Returns (args, by_val): by_val is True when a TreeNode arg came as a value to look up inside the
    first tree (LCA's p and q), in which case LeetCode expects a returned node's value, not its tree.
    One extra trailing int after a single ListNode param is the cycle position (Linked List Cycle).
    """
    params = list(inspect.signature(method).parameters.values())[1:]
    kinds = [_node_kind(p.annotation) for p in params]
    pos = -1
    if len(args) == len(params) + 1 and kinds and kinds[0] == ("ListNode", False) and isinstance(args[-1], int):
        args, pos = args[:-1], args[-1]
    out, root, by_val = list(args), None, False
    for i, (kind, value) in enumerate(zip(kinds, args)):
        if kind is None:
            continue
        name, many = kind
        build = build_list if name == "ListNode" else build_tree
        if many:
            out[i] = [build(v) for v in value]
        elif name == "TreeNode" and root is not None and not isinstance(value, list):
            out[i], by_val = _find(root, value), True
        else:
            out[i] = build_list(value, pos) if name == "ListNode" else build_tree(value)
            if name == "TreeNode" and root is None:
                root = out[i]
    return out, by_val


def returns_node(method) -> bool:
    """True when `method` is annotated to return a single ListNode / TreeNode."""
    kind = _node_kind(inspect.signature(method).return_annotation)
    return kind is not None and not kind[1]


def plain(value, by_val: bool = False, node: bool = False):
    """A returned value as JSON-able data: linked lists and trees serialized the way LeetCode prints them.

    `node`: the method returns a ListNode / TreeNode, so None is the empty one, printed as [].
    """
    if value is None and node and not by_val:
        return []
    if isinstance(value, list):
        return [plain(v, by_val) for v in value]
    if hasattr(value, "val") and hasattr(value, "next"):
        return list_values(value)
    if hasattr(value, "val") and hasattr(value, "left"):
        return value.val if by_val else tree_values(value)
    return value


def run_cases(cls, cases: list[Case]) -> list[Result]:
    design = bool(cases) and design_ops(cases[0]) is not None
    method = None if design else find_method(cls)
    results = []
    for case in cases:
        try:
            if design:
                value = replay(cls, *design_ops(case))
            else:
                args, by_val = node_args(method, [json.loads(a) for a in case.inputs])
                value = plain(method(cls(), *args), by_val, returns_node(method))
        except Exception:
            results.append(Result(case, "error", traceback.format_exc().rstrip()))
            continue
        actual = json.dumps(value, separators=(",", ":"))
        if case.expected is None:
            status = "unchecked"
        else:
            status = "pass" if matches(case.expected, value, case.unordered) else "fail"
        results.append(Result(case, status, actual))
    return results


@dataclass
class Meta:
    id: int
    title: str
    difficulty: str
    slug: str

    @property
    def url(self) -> str:
        return f"https://leetcode.com/problems/{self.slug}/"

    @property
    def stem(self) -> str:
        return f"{self.id:04d}-{self.slug}"


HEADER_RE = re.compile(r"^# (\d+)\. (.+?) \[(\w+)\]\n# https://leetcode\.com/problems/([\w-]+)/", re.M)


def parse_header(text: str) -> Meta:
    m = HEADER_RE.search(text)
    if not m:
        raise ValueError("solve.py has no header; expected '# N. Title [Difficulty]' + URL line (run `lc.py start`)")
    return Meta(int(m.group(1)), m.group(2), m.group(3), m.group(4))


def slug_from_arg(arg: str) -> str:
    m = re.search(r"leetcode\.com/problems/([\w-]+)", arg)
    return m.group(1) if m else arg.strip().strip("/")


def _meta(data: dict) -> Meta:
    return Meta(int(data["questionFrontendId"]), data["title"], data["difficulty"], data["titleSlug"])


def _classname(data: dict) -> str | None:
    """The class a design problem asks for ("MinStack"), or None for a plain `Solution` problem."""
    return json.loads(data["metaData"]).get("classname")


def _snippet_imports(snippet: str) -> str:
    """Only what the snippet's code needs to load: typing names and lc's node classes (its comments don't count)."""
    code = "\n".join(line for line in snippet.splitlines() if not line.lstrip().startswith("#"))
    lines = [f"from typing import {name}" for name in ("List", "Optional") if re.search(rf"\b{name}\[", code)]
    if nodes := [name for name in ("ListNode", "TreeNode") if re.search(rf"\b{name}\b", code)]:
        lines.append(f"from lc import {', '.join(nodes)}")
    return "".join(line + "\n" for line in lines)


def render_solve(data: dict) -> str:
    meta = _meta(data)
    snippet = next(s["code"] for s in data["codeSnippets"] if s["langSlug"] == "python3").rstrip()
    return (
        f"# {meta.id}. {meta.title} [{meta.difficulty}]\n"
        f"# {meta.url}\n"
        f"{_snippet_imports(snippet)}"
        "\n\n"
        f"{snippet}\n"
        "\n\n"
        'if __name__ == "__main__":\n'
        "    import lc\n"
        f"    lc.test({_classname(data) or 'Solution'})\n"
    )


def render_cases(data: dict) -> str:
    # a design problem's example is two lines: the operations and their arguments
    arity = 2 if _classname(data) else len(json.loads(data["metaData"]).get("params", []))
    lines = data["exampleTestcases"].split("\n")
    content = data.get("content") or ""
    # examples are either plain text in <pre> blocks or wrapped in <span class="example-io">
    outputs = [html.unescape(o) for o in re.findall(
        r"<strong>Output:?</strong>\s*(?:<(?:span|code)[^>]*>)?\s*([^\s<].*?)\s*(?:</span>|<|\n)", content)]
    # "return the answer in any order" → compare order-insensitively
    prefix = "~ " if re.search(r"in\s*(<[^>]+>\s*)*any\s*(<[^>]+>\s*)*order", html.unescape(content)) else ""
    blocks = []
    for i in range(0, len(lines), arity):
        block = "\n".join(lines[i : i + arity])
        n = i // arity
        if n < len(outputs):
            block += f"\n=> {prefix}{outputs[n]}"
        blocks.append(block + "\n")
    return "\n".join(blocks)


MARK = {"pass": "✓", "fail": "✗", "unchecked": "·", "error": "!"}


def format_report(results: list[Result]) -> str:
    lines = []
    for i, r in enumerate(results, 1):
        lines.append(f"Case {i}  {MARK[r.status]}")
        if r.status != "pass":
            lines.append("  input:    " + " | ".join(r.case.inputs))
            if r.case.expected is not None:
                lines.append(f"  expected: {r.case.expected}")
            if r.status == "error":
                lines.append("  " + r.actual.replace("\n", "\n  "))
            else:
                lines.append(f"  got:      {r.actual}")
    counts = Counter(r.status for r in results)
    summary = ", ".join(f"{counts[s]} {s}" for s in ("pass", "fail", "unchecked", "error") if counts[s])
    summary = summary.replace(" pass", " passed").replace(" fail", " failed")
    lines += ["", summary or "no cases"]
    return "\n".join(lines) + "\n"


def _problem_row(path: Path) -> tuple[int, str]:
    try:
        meta = parse_header(path.read_text())
        num, title, diff, url = meta.id, meta.title, meta.difficulty, meta.url
    except ValueError:  # legacy file without header: derive from NNNN-slug.py
        num, slug = path.stem.split("-", 1)
        num, title, diff, url = int(num), slug, "", f"https://leetcode.com/problems/{slug}/"
    return num, f"| {num} | [{title}]({url}) | {diff} | [{path.name}](problems/{path.name}) |"


def render_problem_table(root: Path) -> str:
    rows = sorted(_problem_row(p) for p in (root / "problems").glob("[0-9]*.py"))
    return "| # | Problem | Difficulty | Solution |\n|---|---|---|---|\n" + "\n".join(r for _, r in rows) + "\n"


def update_readme(root: Path) -> bool:
    readme = root / "README.md"
    if not readme.exists():
        return False
    text = readme.read_text()
    start, end = "<!-- problems -->\n", "<!-- /problems -->"
    if start not in text or end not in text:
        return False
    head, rest = text.split(start, 1)
    _, tail = rest.split(end, 1)
    readme.write_text(head + start + render_problem_table(root) + end + tail)
    return True


def update_roadmap(root: Path, meta: Meta) -> bool:
    """Tick `- [ ] **N. Title**` in ROADMAP.md and append a [sol] link. False if nothing changed."""
    roadmap = root / "ROADMAP.md"
    if not roadmap.exists():
        return False
    prefix = f"- [ ] **{meta.id}. "
    lines = roadmap.read_text().splitlines(keepends=True)
    for i, line in enumerate(lines):
        if line.startswith(prefix):
            lines[i] = "- [x]" + line[5:].rstrip("\n") + f" · [sol](problems/{meta.stem}.py)\n"
            roadmap.write_text("".join(lines))
            return True
    return False


def strike_roadmap(root: Path, url: str) -> bool:
    """Strike through the ROADMAP.md line for `url` (a premium problem) so `next` skips it. False if nothing changed."""
    roadmap = root / "ROADMAP.md"
    if not roadmap.exists():
        return False
    lines = roadmap.read_text().splitlines(keepends=True)
    for i, line in enumerate(lines):
        if (m := ROADMAP_LINE.match(line)) and m.group(1) == url:
            lines[i] = "- [ ] ~~" + line[6:].rstrip("\n") + "~~ · premium\n"
            roadmap.write_text("".join(lines))
            return True
    return False


def save(root: Path) -> list[Path]:
    """Copy solve.py + cases.txt into problems/ under NNNN-slug names and refresh the README table."""
    meta = parse_header((root / "solve.py").read_text())
    problems = root / "problems"
    problems.mkdir(exist_ok=True)
    written = []
    for src, dst in (("solve.py", f"{meta.stem}.py"), ("cases.txt", f"{meta.stem}.cases.txt")):
        shutil.copyfile(root / src, problems / dst)
        written.append(problems / dst)
    if update_readme(root):
        written.append(root / "README.md")
    if update_roadmap(root, meta):
        written.append(root / "ROADMAP.md")
    return written


class _Markdown(HTMLParser):
    """Enough HTML→markdown for LeetCode statements: p, pre, code, strong/b, em, ul/li, sup."""

    INLINE = {"code": "`", "strong": "**", "b": "**", "em": "*", "i": "*"}

    def __init__(self):
        super().__init__(convert_charrefs=True)
        self.out: list[str] = []
        self.in_pre = False

    def handle_starttag(self, tag, attrs):
        if tag == "pre":
            self.in_pre = True
            self.out.append("\n```\n")
        elif tag == "li":
            self.out.append("\n- ")
        elif tag == "sup":
            self.out.append("^")
        elif tag in ("p", "ul", "div") and not self.in_pre:
            self.out.append("\n\n")
        elif tag in self.INLINE and not self.in_pre:
            self.out.append(self.INLINE[tag])

    def handle_endtag(self, tag):
        if tag == "pre":
            self.in_pre = False
            self.out.append("```\n\n" if self.out[-1].endswith("\n") else "\n```\n\n")
        elif tag in self.INLINE and not self.in_pre:
            self.out.append(self.INLINE[tag])

    def handle_data(self, data):
        if self.in_pre:
            if self.out[-1] == "\n```\n":  # first data inside the block: no leading blank line
                data = data.lstrip("\n")
            self.out.append(data)
        else:
            self.out.append(data.replace("\n", " ").replace("\t", ""))

    def text(self) -> str:
        md = "".join(self.out).replace("\xa0", "")
        md = re.sub(r"[ \t]+\n", "\n", md)  # trailing spaces (also from "&nbsp;" paragraphs)
        md = re.sub(r"\n{3,}", "\n\n", md)
        return md.strip() + "\n"


def html_to_markdown(content: str) -> str:
    parser = _Markdown()
    parser.feed(content)
    return parser.text()


def render_problem(data: dict) -> str:
    meta = _meta(data)
    return f"# {meta.id}. {meta.title} [{meta.difficulty}]\n\n{meta.url}\n\n" + html_to_markdown(data.get("content") or "")


# --- commands -------------------------------------------------------------

ROOT = Path(__file__).resolve().parent

GRAPHQL = "https://leetcode.com/graphql"
QUERY = """query q($slug: String!) { question(titleSlug: $slug) {
  questionFrontendId title titleSlug difficulty exampleTestcases metaData content isPaidOnly
  codeSnippets { langSlug code } } }"""


def fetch(slug: str) -> dict:
    body = json.dumps({"query": QUERY, "variables": {"slug": slug}}).encode()
    headers = {
        "Content-Type": "application/json",
        "Referer": "https://leetcode.com",
        "User-Agent": "Mozilla/5.0 (X11; Linux x86_64) lc.py",  # the default Python-urllib UA gets a 403
    }
    req = urllib.request.Request(GRAPHQL, body, headers)
    try:
        with urllib.request.urlopen(req, timeout=20) as resp:
            data = json.load(resp)["data"]["question"]
    except urllib.error.URLError as e:
        raise ValueError(f"fetching {slug} from LeetCode failed: {e}") from e
    if data is None:
        raise ValueError(f"no such problem: {slug}")
    if data.get("isPaidOnly") or data.get("codeSnippets") is None:
        # premium-locked: LeetCode answers with nulls for content/codeSnippets instead of an error
        raise Premium(f"{data['questionFrontendId']}. {data['title']} is a LeetCode premium problem")
    return data


class Premium(ValueError):
    """The problem is LeetCode-premium: no snippet or examples without a paid account."""


class Unsaved(Exception):
    """solve.py holds a different problem whose contents aren't in problems/ yet."""


def _is_saved(root: Path) -> bool:
    solve = root / "solve.py"
    if not solve.exists():
        return True
    try:
        meta = parse_header(solve.read_text())
    except ValueError:
        return False
    saved = root / "problems" / f"{meta.stem}.py"
    return saved.exists() and saved.read_text() == solve.read_text()


def start(root: Path, arg: str, force: bool = False) -> Meta:
    if not force and not _is_saved(root):
        raise Unsaved("solve.py has unsaved work; commit it or pass --force")
    data = fetch(slug_from_arg(arg))
    (root / "solve.py").write_text(render_solve(data))
    (root / "cases.txt").write_text(render_cases(data))
    (root / "problem.md").write_text(render_problem(data))
    return _meta(data)


ROADMAP_LINE = re.compile(r"^- \[ \] \*\*\d+\. .*?\[LC\]\((https://leetcode\.com/problems/[\w-]+/?)\)")


def next_unsolved(root: Path) -> str | None:
    """URL of the first unticked problem in ROADMAP.md (topic order), or None."""
    roadmap = root / "ROADMAP.md"
    if not roadmap.exists():
        return None
    for line in roadmap.read_text().splitlines():
        if m := ROADMAP_LINE.match(line):
            return m.group(1)
    return None


def unticked_urls(root: Path) -> list[str]:
    roadmap = root / "ROADMAP.md"
    if not roadmap.exists():
        return []
    return [m.group(1) for line in roadmap.read_text().splitlines() if (m := ROADMAP_LINE.match(line))]


@dataclass
class PathEntry:
    id: int
    slug: str
    day: date | None = None


PATH_LINE = re.compile(r"^(?:(\d{4}-\d{2}-\d{2})\s+)?(\d+)\s+([\w-]+)$")


def read_path(root: Path, name: str) -> dict[str, list[PathEntry]]:
    """paths/<name>.txt: `[core]` / `[stretch]` / `[mock]` sections of `[YYYY-MM-DD] N slug` lines, `#` comments."""
    sections, current = {}, None
    for line in (root / "paths" / f"{name}.txt").read_text().splitlines():
        line = line.split("#", 1)[0].strip()
        if not line:
            continue
        if line.startswith("[") and line.endswith("]"):
            current = sections.setdefault(line[1:-1], [])
        elif current is not None and (m := PATH_LINE.match(line)):
            current.append(PathEntry(int(m.group(2)), m.group(3), date.fromisoformat(m.group(1)) if m.group(1) else None))
        else:
            raise ValueError(f"paths/{name}.txt: can't read {line!r}")
    return sections


def solved_slugs(root: Path) -> set[str]:
    """Slugs saved in problems/ (NNNN-slug.py): what a path counts as done."""
    return {f.stem.split("-", 1)[1] for f in (root / "problems").glob("*.py") if "-" in f.stem}


def path_next(root: Path, name: str) -> str | None:
    """First unsolved slug in the path's core, then stretch; mock problems are never handed out."""
    sections, done = read_path(root, name), solved_slugs(root)
    for entry in sections.get("core", []) + sections.get("stretch", []):
        if entry.slug not in done:
            return entry.slug
    return None


def path_status(root: Path, name: str, today: date) -> str:
    """"core 3/16 · stretch 0/4 · today: 875, 153 · behind: 3"."""
    sections, done = read_path(root, name), solved_slugs(root)
    parts = []
    for section in ("core", "stretch"):
        entries = sections.get(section, [])
        if entries:
            parts.append(f"{section} {sum(e.slug in done for e in entries)}/{len(entries)}")
    open_core = [e for e in sections.get("core", []) if e.slug not in done and e.day]
    for label, keep in (("today", lambda d: d == today), ("behind", lambda d: d < today)):
        if ids := [str(e.id) for e in open_core if keep(e.day)]:
            parts.append(f"{label}: {', '.join(ids)}")
    return " · ".join(parts)


SMOKE_PAUSE = 0.4  # seconds between LeetCode requests


def smoke(root: Path, fetch=None, pause: float | None = None, log=lambda slug, kind, msg: None) -> list[tuple[str, str]]:
    """Render every unticked ROADMAP problem in memory (writes nothing, no Discord); [(slug, issue)] for the broken ones.

    `log(slug, kind, msg)` sees every problem as it goes; kind is "ok", "premium" or "issue"."""
    fetch = fetch or globals()["fetch"]
    pause = SMOKE_PAUSE if pause is None else pause
    issues = []
    for n, url in enumerate(unticked_urls(root)):
        if n and pause:
            time.sleep(pause)
        slug = slug_from_arg(url)
        try:
            data = fetch(slug)
            render_solve(data)
            render_problem(data)
            cases = parse_cases(render_cases(data))
        except Premium:
            log(slug, "premium", "premium, skipped")
            continue
        except Exception as e:  # noqa: BLE001 — any crash is what smoke is looking for
            issues.append((slug, f"crash: {type(e).__name__}: {e}"))
        else:
            missing = [i for i, c in enumerate(cases, 1) if not c.expected]
            if not cases:
                issues.append((slug, "no cases"))
            elif missing:
                issues.append((slug, f"missing expected output in case(s) {missing}"))
            else:
                log(slug, "ok", f"ok ({len(cases)} cases)")
                continue
        log(slug, "issue", issues[-1][1])
    return issues


def add(root: Path, inputs: list[str], expected: str | None) -> None:
    path = root / "cases.txt"
    text = path.read_text() if path.exists() else ""
    block = "\n".join(inputs) + (f"\n=> {expected}" if expected else "") + "\n"
    if text and not text.endswith("\n"):
        text += "\n"
    path.write_text(text + ("\n" if text else "") + block)


def load_solution(root: Path):
    spec = importlib.util.spec_from_file_location("solve", root / "solve.py")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    if hasattr(module, "Solution"):
        return module.Solution
    # design problem: the class is the first operation of the first case
    cases = parse_cases((root / "cases.txt").read_text())
    if cases and (ops := design_ops(cases[0])) and hasattr(module, ops[0][0]):
        return getattr(module, ops[0][0])
    raise ValueError("solve.py defines no Solution class (nor the class cases.txt constructs)")


def test(cls, root: Path | None = None) -> int:
    """Run cases.txt against `cls`, print the report; returns the number of non-passing checked cases."""
    root = root or ROOT
    results = run_cases(cls, parse_cases((root / "cases.txt").read_text()))
    print(format_report(results), end="")
    return sum(r.status in ("fail", "error") for r in results)


WORKING_FILES = ("solve.py", "cases.txt", "problem.md")


def commit_message(meta: Meta) -> str:
    return f"feat: solved {meta.id}. {meta.title} [{meta.difficulty}]"


def commit(root: Path) -> int:
    """Stage the working files and commit them; the pre-commit hook does the saving."""
    meta = parse_header((root / "solve.py").read_text())
    files = [f for f in WORKING_FILES if (root / f).exists()]
    subprocess.run(["git", "add", "--", *files], cwd=root, check=True)
    return subprocess.run(["git", "commit", "-m", commit_message(meta)], cwd=root).returncode


def _prompt_case() -> tuple[list[str], str | None]:
    print("input args, one per line (blank line to finish):")
    inputs = []
    while (line := input().strip()):
        inputs.append(line)
    expected = input("expected output (blank for none): ").strip()
    return inputs, expected or None


def main(argv: list[str], root: Path | None = None) -> int:
    root = root or ROOT
    parser = argparse.ArgumentParser(prog="lc", description=__doc__)
    sub = parser.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("start", help="fetch a problem into solve.py + cases.txt")
    p.add_argument("problem", help="LeetCode URL or title slug")
    p.add_argument("--force", action="store_true", help="overwrite solve.py even if unsaved")
    p = sub.add_parser("next", help="start the first unsolved problem in ROADMAP.md")
    p.add_argument("--force", action="store_true", help="overwrite solve.py even if unsaved")
    p = sub.add_parser("path", help="start the next problem on paths/<name>.txt (core, then stretch)")
    p.add_argument("name", nargs="?", default="interview", help="path file under paths/ (default: interview)")
    p.add_argument("--force", action="store_true", help="overwrite solve.py even if unsaved")
    sub.add_parser("test", help="run cases.txt against solve.py")
    sub.add_parser("add", help="append a case to cases.txt (interactive)")
    sub.add_parser("save", help="copy solve.py + cases.txt into problems/ and refresh README")
    sub.add_parser("smoke", help="render every unticked ROADMAP problem from live LeetCode, report breakage (writes nothing)")
    sub.add_parser("commit", help="git commit solve.py/cases.txt/problem.md as 'feat: solved N. Title'")
    args = parser.parse_args(argv)
    try:
        return _dispatch(args, root)
    except SyntaxError as e:
        # "expected an indented block after function definition on line 13" is reported at a later
        # line; point at the empty def itself since that's where the fix goes
        m = re.fullmatch(r"(.*) on line (\d+)", e.msg)
        lineno, msg = (m.group(2), m.group(1)) if m else (e.lineno, e.msg)
        print(f"lc: solve.py line {lineno}: {msg}", file=sys.stderr)
        return 1
    except (FileNotFoundError, ValueError) as e:
        print(f"lc: {e}", file=sys.stderr)
        return 1


def announce_start(meta: Meta) -> None:
    """Open the problem's Discord post as In Progress, if Discord is configured; failures only warn."""
    import discord

    config = discord.load_config()
    if config is None:
        return
    try:
        print("discord: " + discord.start_post(meta, config, discord.Api(config["token"])))
    except Exception as e:  # noqa: BLE001 — Discord being down must not undo a successful start
        print(f"discord: {e}", file=sys.stderr)


def _dispatch(args, root: Path) -> int:
    if args.cmd in ("start", "next", "path"):
        if args.cmd == "path":
            print(path_status(root, args.name, date.today()))
        while True:
            if args.cmd == "path":
                problem = path_next(root, args.name)
                if problem is None:
                    print(f"lc: paths/{args.name}.txt core and stretch are done; mock problems stay closed for mock days",
                          file=sys.stderr)
                    return 1
            else:
                problem = args.problem if args.cmd == "start" else next_unsolved(root)
            if problem is None:
                print("lc: nothing left unticked in ROADMAP.md", file=sys.stderr)
                return 1
            try:
                meta = start(root, problem, args.force)
                break
            except Unsaved as e:
                print(f"lc: {e}", file=sys.stderr)
                return 1
            except Premium as e:
                if args.cmd != "next":
                    raise
                # strike it out so the roadmap moves past it, then try the following problem
                strike_roadmap(root, problem)
                print(f"lc: {e}; struck it from ROADMAP.md", file=sys.stderr)
        print(f"{meta.id}. {meta.title} [{meta.difficulty}] -> solve.py, cases.txt, problem.md")
        announce_start(meta)
    elif args.cmd == "test":
        return 1 if test(load_solution(root), root) else 0
    elif args.cmd == "add":
        inputs, expected = _prompt_case()
        if not inputs:
            print("no inputs given", file=sys.stderr)
            return 1
        add(root, inputs, expected)
    elif args.cmd == "save":
        for path in save(root):
            print(f"wrote {path.relative_to(root)}")
    elif args.cmd == "commit":
        return commit(root)
    elif args.cmd == "smoke":
        kinds = Counter()

        def log(slug, kind, msg):
            kinds[kind] += 1
            print(f"  {slug}: {msg}", flush=True)

        issues = smoke(root, log=log)
        premium, checked = kinds["premium"], kinds["ok"] + kinds["issue"]
        print(f"\nsmoke: {len(issues)} of {checked} problems have issues ({premium} premium skipped)")
        for slug, issue in issues:
            print(f"  {slug}: {issue}")
        return 1 if issues else 0
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
