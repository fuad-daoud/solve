# 11. Container With Most Water [Medium]
# https://leetcode.com/problems/container-with-most-water/


class Solution:
    def maxArea(self, height: list[int]) -> int:
        n = len(height)
        l, r = 0, n - 1
        answer = -1
        while l < r:
            area = min(height[l], height[r]) * (r - l)
            answer = max(answer, area)
            if height[l] >= height[r]:
                r -= 1
            elif height[l] < height[r]:
                l += 1

        return answer


if __name__ == "__main__":
    import lc

    lc.test(Solution)
