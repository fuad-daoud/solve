# Solve

LeetCode workbench in Python. Two files you touch: `solve.py` (the current problem) and `cases.txt` (its test cases).

## Setup

```sh
make setup   # once per clone: installs the pre-commit hook
```

## Workflow

```sh
make next                                             # first unticked problem in ROADMAP.md → solve.py, cases.txt, problem.md
make start P=https://leetcode.com/problems/two-sum/   # …or any problem by URL / slug
make test                                             # run every case, LeetCode-style report
make commit                                           # "feat: solved 1. Two Sum [Easy]"; hook saves to problems/ + updates tables
```

In neovim, `<leader>rp` from `solve.py` runs `make test` into a right-hand column (`cases.txt` on top, report below);
`<leader>rd` opens the problem statement (`problem.md`) in a new tab.

A Socratic coach lives under `<leader>a` (Claude Code session per problem, never hands over the solution):
`<leader>ah` next hint (4-rung ladder), `<leader>aa` ask about the selection, `<leader>ar` review the attempt,
`<leader>ad` debrief once solved (reveals the approach — asks first if tests still fail), `<leader>at` toggle the pane,
`<leader>ac` terminal chat. Also `:Solve`, `:SolveHint`, `:SolveAsk`, `:SolveReview`, `:SolveDebrief`, `:SolveChat`.

### cases.txt

One JSON argument per line, exactly as LeetCode's testcase box shows them. Blank line between cases.
`=> value` is the expected output (optional); `=> ~ value` compares lists ignoring order.

```
[2,7,11,15]
9
=> [0,1]

[3,3]
6
```

`make add` appends a case interactively, or just edit the file.

### Saving

`make commit` stages `solve.py`, `cases.txt`, `problem.md` and commits as `feat: solved N. Title [Difficulty]`.
The pre-commit hook fires only when `solve.py` is staged. It refuses the commit if `cases.txt` has failures
(`--no-verify` to override), then copies `solve.py` → `problems/NNNN-slug.py`, `cases.txt` → `problems/NNNN-slug.cases.txt`,
regenerates the table below, ticks the problem in `ROADMAP.md`, and stages all of it. `make save` does the same by hand.

`make start` refuses to overwrite `solve.py` while it holds unsaved work on a different problem (`--force` via `python3 lc.py start --force …`).

### Discord

Mirrors the forum-post-per-problem routine, in the channel for the problem's difficulty
(skipped silently when `~/.config/solve/discord.json` doesn't exist; a Discord failure is printed but never fails the command):

- `make start` / `make next` creates the post — title, `In Progress` tag, the LeetCode URL as the first message —
  unless a post with that title already exists (yours or a friend's), which is left untouched.
- the post-commit hook, after a commit that includes `solve.py`, swaps `In Progress` / `Not Solved` for `Solved`
  (other tags are kept) and posts the `class Solution` body in a ` ```py ` block (header, imports and harness stripped).
  No post yet → it is created tagged `Solved`. Re-committing the same code is a no-op.

One-time setup: create an application at <https://discord.com/developers/applications> → *Bot* → copy the token;
invite it with *View Channels, Send Messages, Send Messages in Threads, Create Public Threads, Read Message History,
Manage Threads* (needed to apply the `Solved` tag when it is a mod-only tag)
(*OAuth2 → URL Generator*, scope `bot`); turn on *Developer Mode* in Discord's settings and right-click each forum
channel → *Copy Channel ID*. Then:

```json
// ~/.config/solve/discord.json — one forum channel id per difficulty; missing ones are skipped
{ "token": "…", "channels": { "Easy": "123…", "Medium": "456…" } }
```

## Layout

```
solve.py  cases.txt   working files (+ problem.md, the statement)
lc.py                 the tool (stdlib only); `make check` runs its tests
discord.py            posts solutions to Discord (used by .githooks/post-commit)
problems/             saved solutions + their cases
archive/              pre-2026 Codeforces / AtCoder / C++ / Elixir era (see archive/README.md)
```

## Solved

<!-- problems -->
| # | Problem | Difficulty | Solution |
|---|---|---|---|
| 1 | [Two Sum](https://leetcode.com/problems/two-sum/) | Easy | [0001-two-sum.py](problems/0001-two-sum.py) |
| 6 | [Zigzag Conversion](https://leetcode.com/problems/zigzag-conversion/) | Medium | [0006-zigzag-conversion.py](problems/0006-zigzag-conversion.py) |
| 15 | [3Sum](https://leetcode.com/problems/3sum/) | Medium | [0015-3sum.py](problems/0015-3sum.py) |
| 22 | [Generate Parentheses](https://leetcode.com/problems/generate-parentheses/) | Medium | [0022-generate-parentheses.py](problems/0022-generate-parentheses.py) |
| 26 | [Remove Duplicates from Sorted Array](https://leetcode.com/problems/remove-duplicates-from-sorted-array/) | Easy | [0026-remove-duplicates-from-sorted-array.py](problems/0026-remove-duplicates-from-sorted-array.py) |
| 49 | [Group Anagrams](https://leetcode.com/problems/group-anagrams/) | Medium | [0049-group-anagrams.py](problems/0049-group-anagrams.py) |
| 66 | [Plus One](https://leetcode.com/problems/plus-one/) | Easy | [0066-plus-one.py](problems/0066-plus-one.py) |
| 122 | [Best Time to Buy and Sell Stock II](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/) | Medium | [0122-best-time-to-buy-and-sell-stock-ii.py](problems/0122-best-time-to-buy-and-sell-stock-ii.py) |
| 136 | [Single Number](https://leetcode.com/problems/single-number/) | Easy | [0136-single-number.py](problems/0136-single-number.py) |
| 189 | [Rotate Array](https://leetcode.com/problems/rotate-array/) | Medium | [0189-rotate-array.py](problems/0189-rotate-array.py) |
| 217 | [Contains Duplicate](https://leetcode.com/problems/contains-duplicate/) | Easy | [0217-contains-duplicate.py](problems/0217-contains-duplicate.py) |
| 238 | [Product of Array Except Self](https://leetcode.com/problems/product-of-array-except-self/) | Medium | [0238-product-of-array-except-self.py](problems/0238-product-of-array-except-self.py) |
| 242 | [Valid Anagram](https://leetcode.com/problems/valid-anagram/) | Easy | [0242-valid-anagram.py](problems/0242-valid-anagram.py) |
| 347 | [Top K Frequent Elements](https://leetcode.com/problems/top-k-frequent-elements/) | Medium | [0347-top-k-frequent-elements.py](problems/0347-top-k-frequent-elements.py) |
| 350 | [Intersection of Two Arrays II](https://leetcode.com/problems/intersection-of-two-arrays-ii/) | Easy | [0350-intersection-of-two-arrays-ii.py](problems/0350-intersection-of-two-arrays-ii.py) |
<!-- /problems -->
