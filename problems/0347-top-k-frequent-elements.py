# 347. Top K Frequent Elements [Medium]
# https://leetcode.com/problems/top-k-frequent-elements/
import bisect
import functools
import heapq
import itertools
import math
from collections import *
from typing import *


class Solution:
    def topKFrequent(self, nums: list[int], k: int) -> list[int]:
        answer = {}
        for n in nums:
            if n not in answer:
                answer[n] = 0
            answer[n] = answer[n] + 1

        s = list(
            reversed(
                list(dict(sorted(answer.items(), key=lambda item: item[1])).keys())
            )
        )
        return s[:k]


if __name__ == "__main__":
    import lc

    lc.test(Solution)
