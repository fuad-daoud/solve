# 1. Two Sum [Easy]
# https://leetcode.com/problems/two-sum/
from typing import List


def two_sum(nums: List[int], target: int) -> List[int]:
    seen = {}
    for i, n in enumerate(nums):
        if target - n in seen:
            return [seen[target - n], i]
        seen[n] = i
    return []

