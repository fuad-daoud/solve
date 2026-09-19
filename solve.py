# 128. Longest Consecutive Sequence [Medium]
# https://leetcode.com/problems/longest-consecutive-sequence/


class Solution:
    def longestConsecutive(self, nums: list[int]) -> int:
        if len(nums) == 0:
            return 0
        st = set(nums)
        answer = 0
        for n in st:
            if n - 1 in st:
                continue
            length = 1
            while n + length in st:
                length += 1
            answer = max(answer, length)

        return answer


if __name__ == "__main__":
    import lc

    lc.test(Solution)
