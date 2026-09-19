# 128. Longest Consecutive Sequence [Medium]
# https://leetcode.com/problems/longest-consecutive-sequence/


class Solution:
    def longestConsecutive(self, nums: list[int]) -> int:
        if len(nums) == 0:
            return 0
        nums = list(dict.fromkeys(sorted(nums)))
        answer = 0
        current = 0
        prev = nums[0]
        for i in range(1, len(nums)):
            n = nums[i]
            if abs(n - prev) == 1:
                current += 1
                answer = max(current, answer)
            else:
                current = 0
            prev = n

        return answer + 1


if __name__ == "__main__":
    import lc

    lc.test(Solution)
