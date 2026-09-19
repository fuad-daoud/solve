# 36. Valid Sudoku [Medium]
# https://leetcode.com/problems/valid-sudoku/


class Solution:
    def isValidSudoku(self, board: list[list[str]]) -> bool:
        N = 9
        for i in range(N):
            numbers = set()
            for j in range(N):
                cell = board[i][j]
                if cell == ".":
                    continue
                if cell in numbers:
                    return False
                numbers.add(cell)

        for i in range(N):
            numbers = set()
            for j in range(N):
                cell = board[j][i]
                if cell == ".":
                    continue
                if cell in numbers:
                    return False
                numbers.add(cell)

        M = 3
        for k in range(M):
            for l in range(M):
                numbers = set()
                for i in range(M):
                    for j in range(M):
                        cell = board[i + (k * M)][j + (l * M)]
                        if cell == ".":
                            continue
                        if cell in numbers:
                            print("numbers", numbers)
                            print("cell", cell)
                            return False
                        numbers.add(cell)

        return True


if __name__ == "__main__":
    import lc

    lc.test(Solution)
