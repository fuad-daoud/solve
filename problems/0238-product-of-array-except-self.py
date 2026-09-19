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
        n = len(nums)
        answer = [1] * n
        for i in range(1, n):
            answer[i] = answer[i - 1] * nums[i - 1]

        product = 1
        for i in range(n - 1, -1, -1):
            answer[i] *= product
            product *= nums[i]
        return answer


if __name__ == "__main__":
    import lc

    lc.test(Solution)
