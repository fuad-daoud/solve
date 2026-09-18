# Solve

LeetCode workbench in Python. Two files you touch: `solve.py` (the current problem) and `cases.txt` (its test cases).

## Setup

```sh
make setup   # once per clone: installs the pre-commit hook
```

## Workflow

```sh
make start P=https://leetcode.com/problems/two-sum/   # fetch problem → solve.py, cases.txt, problem.md
make test                                             # run every case, LeetCode-style report
git commit -am "solved 1"                             # hook saves to problems/ and updates the table below
```

In neovim, `<leader>rp` from `solve.py` runs `make test` into a right-hand column (`cases.txt` on top, report below);
`<leader>rd` opens the problem statement (`problem.md`) in a new tab.

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

The pre-commit hook fires only when `solve.py` is staged. It refuses the commit if `cases.txt` has failures
(`--no-verify` to override), then copies `solve.py` → `problems/NNNN-slug.py`, `cases.txt` → `problems/NNNN-slug.cases.txt`,
regenerates the table below, ticks the problem in `ROADMAP.md`, and stages all of it. `make save` does the same by hand.

`make start` refuses to overwrite `solve.py` while it holds unsaved work on a different problem (`--force` via `python3 lc.py start --force …`).

## Layout

```
solve.py  cases.txt   working files (+ problem.md, the statement)
lc.py                 the tool (stdlib only); `make check` runs its tests
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
| 66 | [Plus One](https://leetcode.com/problems/plus-one/) | Easy | [0066-plus-one.py](problems/0066-plus-one.py) |
| 122 | [Best Time to Buy and Sell Stock II](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/) | Medium | [0122-best-time-to-buy-and-sell-stock-ii.py](problems/0122-best-time-to-buy-and-sell-stock-ii.py) |
| 136 | [Single Number](https://leetcode.com/problems/single-number/) | Easy | [0136-single-number.py](problems/0136-single-number.py) |
| 189 | [Rotate Array](https://leetcode.com/problems/rotate-array/) | Medium | [0189-rotate-array.py](problems/0189-rotate-array.py) |
| 217 | [Contains Duplicate](https://leetcode.com/problems/contains-duplicate/) | Easy | [0217-contains-duplicate.py](problems/0217-contains-duplicate.py) |
| 350 | [Intersection of Two Arrays II](https://leetcode.com/problems/intersection-of-two-arrays-ii/) | Easy | [0350-intersection-of-two-arrays-ii.py](problems/0350-intersection-of-two-arrays-ii.py) |
<!-- /problems -->
