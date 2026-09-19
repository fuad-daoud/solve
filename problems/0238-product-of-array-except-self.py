# 238. Product of Array Except Self [Medium]
# https://leetcode.com/problems/product-of-array-except-self/
import bisect
import functools
import heapq
import itertools
import math
from collections import *
from typing import *


class Solution:
    def productExceptSelf(self, nums: list[int]) -> list[int]:
        allProduct = 0
        zeroes = 0
        answer = []
        for n in nums:
            if n == 0:
                zeroes = zeroes + 1
                continue
            if allProduct == 0:
                allProduct = n
                continue
            allProduct = allProduct * n
        for n in nums:
            if zeroes > 1:
                answer.append(0)
                continue
            if zeroes == 1 and n != 0:
                answer.append(0)
                continue
            if n == 0:
                answer.append(allProduct)
            else:
                answer.append(allProduct // n)
        return answer


if __name__ == "__main__":
    import lc

    lc.test(Solution)
