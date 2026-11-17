# 424. Longest Repeating Character Replacement [Medium]
# https://leetcode.com/problems/longest-repeating-character-replacement/


class Solution:
    def characterReplacement(self, s: str, k: int) -> int:
        count = {}
        left = maxf = 0
        for right, ch in enumerate(s):
            count[ch] = count.get(ch, 0) + 1
            maxf = max(maxf, count[ch])
            if (right - left + 1) - maxf > k:
                count[s[left]] -= 1
                left += 1
        return len(s) - left


if __name__ == "__main__":
    import lc

    lc.test(Solution)
