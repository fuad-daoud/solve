# 424. Longest Repeating Character Replacement [Medium]
# https://leetcode.com/problems/longest-repeating-character-replacement/


class Solution:
    def characterReplacement(self, s: str, k: int) -> int:
        count = [0] * 26
        left = best = 0
        for right, ch in enumerate(s):
            count[ord(ch) - 65] += 1
            while (right - left + 1) - max(count) > k:
                count[ord(s[left]) - 65] -= 1
                left += 1
            best = max(best, right - left + 1)
        return best


if __name__ == "__main__":
    import lc

    lc.test(Solution)
