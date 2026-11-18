# 567. Permutation in String [Medium]
# https://leetcode.com/problems/permutation-in-string/


class Solution:
    def checkInclusion(self, s1: str, s2: str) -> bool:
        if len(s1) > len(s2):
            return False
        need, have = [0] * 26, [0] * 26
        for i in range(len(s1)):
            need[ord(s1[i]) - 97] += 1
            have[ord(s2[i]) - 97] += 1
        matches = sum(need[c] == have[c] for c in range(26))
        for r in range(len(s1), len(s2)):
            if matches == 26:
                return True
            c = ord(s2[r]) - 97
            have[c] += 1
            if have[c] == need[c]:
                matches += 1
            elif have[c] == need[c] + 1:
                matches -= 1
            c = ord(s2[r - len(s1)]) - 97
            have[c] -= 1
            if have[c] == need[c]:
                matches += 1
            elif have[c] == need[c] - 1:
                matches -= 1

        return matches == 26


if __name__ == "__main__":
    import lc

    lc.test(Solution)
