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
        l, r = 0, len(s) - 1
        while l < r:
            while l < r and not s[l].isalnum():
                l += 1
            while l < r and not s[r].isalnum():
                r -= 1
            if s[l].lower() != s[r].lower():
                return False
            l += 1
            r -= 1
        return True


if __name__ == "__main__":
    import lc

    lc.test(Solution)
