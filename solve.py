# 3. Longest Substring Without Repeating Characters [Medium]
# https://leetcode.com/problems/longest-substring-without-repeating-characters/


class Solution:
    def lengthOfLongestSubstring(self, string: str) -> int:
        if len(string) == 0:
            return 0
        left = 0
        answer = 1
        chars = {string[left]: 0}
        for right in range(2, len(string) + 1):
            if string[right - 1] in chars:
                value = chars.pop(string[right - 1]) + 1
                while left != value and string[left] in chars:
                    chars.pop(string[left])
                    left += 1
                left = value
            chars[string[right - 1]] = right - 1
            answer = max(answer, right - left)
        return answer


if __name__ == "__main__":
    import lc

    lc.test(Solution)
