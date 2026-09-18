# 22. Generate Parentheses [Medium]
# https://leetcode.com/problems/generate-parentheses/
import bisect
import functools
import heapq
import itertools
import math
from collections import *
from typing import *


class Solution:
    def generateParenthesis(self, n: int) -> list[str]:
        answer = []

        def calc(s, opened, closed):
            if len(s) == n * 2:
                if closed == opened:
                    answer.append(s)
                return
            if closed < opened:
                calc(s + ")", opened, closed + 1)
            if opened < n:
                calc(s + "(", opened + 1, closed)

        calc("(", 1, 0)
        return answer


if __name__ == "__main__":
    import lc

    lc.test(Solution)
