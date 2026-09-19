# 125. Valid Palindrome [Easy]
# https://leetcode.com/problems/valid-palindrome/
import bisect
import functools
import heapq
import itertools
import math
from collections import *
from typing import *


class Solution:
    def isPalindrome(self, s: str) -> bool:
        s = "".join(filter(str.isalnum, s)).lower()

        n = len(s)
        for i in range(n):
            if s[i] != s[n - i - 1]:
                return False
        return True


if __name__ == "__main__":
    import lc

    lc.test(Solution)
