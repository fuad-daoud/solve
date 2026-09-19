# 36. Valid Sudoku [Medium]
# https://leetcode.com/problems/valid-sudoku/


from collections import defaultdict


class Solution:
    def isValidSudoku(self, board: list[list[str]]) -> bool:
        N = 9
        rows = defaultdict(set)
        cols = defaultdict(set)
        boxes = defaultdict(set)

        for r in range(N):
            for c in range(N):
                v = board[r][c]
                if v == ".":
                    continue
                b = (r // 3, c // 3)
                if v in rows[r] or v in cols[c] or v in boxes[b]:
                    return False
                rows[r].add(v)
                cols[c].add(v)
                boxes[b].add(v)

        return True


if __name__ == "__main__":
    import lc

    lc.test(Solution)
