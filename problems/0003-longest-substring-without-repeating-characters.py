# 3. Longest Substring Without Repeating Characters [Medium]
# https://leetcode.com/problems/longest-substring-without-repeating-characters/


class Solution:
    def lengthOfLongestSubstring(self, string: str) -> int:
        seen = set()
        left = best = 0
        for right, c in enumerate(string):
            while c in seen:
                seen.remove(string[left])
                left += 1
            seen.add(c)
            best = max(best, right - left + 1)
        return best


if __name__ == "__main__":
    import lc

    lc.test(Solution)
