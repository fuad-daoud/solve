# 153. Find Minimum in Rotated Sorted Array [Medium]
# https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/


class Solution:
    def findMin(self, nums: list[int]) -> int:
        return min(nums)


if __name__ == "__main__":
    import lc

    lc.test(Solution)
