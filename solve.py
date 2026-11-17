# 3. Longest Substring Without Repeating Characters [Medium]
# https://leetcode.com/problems/longest-substring-without-repeating-characters/


class Solution:
    def lengthOfLongestSubstring(self, string: str) -> int:
        last = {}
        left = best = 0
        for right, c in enumerate(string):
            if last.get(c, -1) >= left:  # duplicate is inside the window
                left = last[c] + 1
            last[c] = right
            best = max(best, right - left + 1)
        return best


if __name__ == "__main__":
    import lc

    lc.test(Solution)
