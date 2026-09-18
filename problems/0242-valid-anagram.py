# 242. Valid Anagram [Easy]
# https://leetcode.com/problems/valid-anagram/
import bisect
import functools
import heapq
import itertools
import math
from collections import *
from typing import *


class Solution:
    def isAnagram(self, s: str, t: str) -> bool:
        return Counter(s) == Counter(t)


if __name__ == "__main__":
    import lc

    lc.test(Solution)
