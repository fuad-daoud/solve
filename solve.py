# 20. Valid Parentheses [Easy]
# https://leetcode.com/problems/valid-parentheses/


class Solution:
    def isValid(self, s: str) -> bool:
        pairs = {")": "(", "]": "[", "}": "{"}
        st = []
        for c in s:
            if c in pairs:
                if not st or st.pop() != pairs[c]:
                    return False
            else:
                st.append(c)
        return not st


if __name__ == "__main__":
    import lc

    lc.test(Solution)
