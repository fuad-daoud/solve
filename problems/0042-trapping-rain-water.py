# 42. Trapping Rain Water [Hard]
# https://leetcode.com/problems/trapping-rain-water/


class Solution:
    def trap(self, height: list[int]) -> int:
        current = 0
        current_area = 0
        prev = 0
        answer = 0
        while current != len(height):
            if prev <= height[current]:
                answer += current_area
                prev = height[current]
                current_area = 0
            else:
                current_area += prev - height[current]
            current += 1

        current = 0
        current_area = 0
        prev = 0
        height = list(reversed(height))
        while current != len(height):
            if prev < height[current]:
                answer += current_area
                prev = height[current]
                current_area = 0
            else:
                current_area += prev - height[current]
            current += 1
        return answer


if __name__ == "__main__":
    import lc

    lc.test(Solution)
