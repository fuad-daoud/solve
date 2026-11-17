# 53. Maximum Subarray [Medium]
# https://leetcode.com/problems/maximum-subarray/


# Kadane's algorithm


class Solution:
    def maxSubArray(self, nums: list[int]) -> int:
        sm = nums[0]
        answer = sm
        for i in range(1, len(nums)):
            d = nums[i]
            sm = max(d, sm + d)
            answer = max(answer, sm)
        return answer


if __name__ == "__main__":
    import lc

    lc.test(Solution)
