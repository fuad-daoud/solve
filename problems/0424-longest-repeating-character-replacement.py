# 424. Longest Repeating Character Replacement [Medium]
# https://leetcode.com/problems/longest-repeating-character-replacement/

import string


class Solution:
    def characterReplacement(self, s: str, k: int) -> int:
        freqs = {}
        for letter in string.ascii_uppercase:
            freqs[letter] = 0
        left = 0
        answer = 0
        mx = -1
        for right in range(len(s)):
            # add to the substring
            freqs[s[right]] += 1
            mx = max(mx, freqs[s[right]])

            # is valid sub string ?
            if (right - left + 1) - mx <= k:
                answer = max(answer, (right - left) + 1)
            else:
                toRemove = s[left]
                while s[left] == toRemove and not ((right - left + 1) - mx <= k):
                    freqs[s[left]] -= 1
                    left += 1

        return answer


if __name__ == "__main__":
    import lc

    lc.test(Solution)
