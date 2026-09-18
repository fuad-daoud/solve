# 49. Group Anagrams [Medium]
# https://leetcode.com/problems/group-anagrams/
import bisect
import functools
import heapq
import itertools
import math
from collections import *
from typing import *


class Solution:
    def groupAnagrams(self, strs: list[str]) -> list[list[str]]:
        answer = {}
        for s in strs:
            sorted_key = "".join(sorted(s))
            answer.setdefault(sorted_key, []).append(s)
        return list(answer.values())


if __name__ == "__main__":
    import lc

    lc.test(Solution)
