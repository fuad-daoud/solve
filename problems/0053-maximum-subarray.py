# 53. Maximum Subarray [Medium]
# https://leetcode.com/problems/maximum-subarray/


# divide & conquer


class Solution:
    def maxSubArray(self, nums: list[int]) -> int:
        return solve(nums, 0, len(nums))


def solve(nums: list[int], left, right):
    split = (left + right) // 2

    if right - left == 1:
        return max(nums[left], nums[right - 1])
    if right - left < 3:
        return max(nums[left], nums[left] + nums[right - 1], nums[right - 1])

    ## cross check
    rightSum = 0
    rightBest = nums[split]
    for i in range(split, right):
        rightSum = rightSum + nums[i]
        rightBest = max(rightBest, rightSum)

    leftSum = 0
    leftBest = nums[split - 1]
    for i in range(split - 1, left - 1, -1):
        leftSum = leftSum + nums[i]
        leftBest = max(leftBest, leftSum)

    return max(
        solve(nums, left, split),
        rightBest + leftBest,
        solve(nums, split, right),
    )


if __name__ == "__main__":
    import lc

    lc.test(Solution)
