# 567. Permutation in String [Medium]
# https://leetcode.com/problems/permutation-in-string/


class Solution:
    def checkInclusion(self, s1: str, s2: str) -> bool:
        if len(s1) > len(s2):
            return False
        left = 0
        s1Freqs = {}
        for s in s1:
            s1Freqs[s] = s1Freqs.get(s, 0) + 1
        permFreqs = {}
        for right in range(len(s2)):
            permFreqs[s2[right]] = permFreqs.get(s2[right], 0) + 1
            if (right - left) < len(s1) - 1:
                continue

            if (right - left) > len(s1) - 1:
                permFreqs[s2[left]] -= 1
                if permFreqs[s2[left]] == 0:
                    permFreqs.pop(s2[left])
                left += 1
            if s1Freqs == permFreqs:
                return True

        return False


if __name__ == "__main__":
    import lc

    lc.test(Solution)
