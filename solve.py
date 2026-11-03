# 20. Valid Parentheses [Easy]
# https://leetcode.com/problems/valid-parentheses/


class Solution:
    def isValid(self, string: str) -> bool:
        st = []
        closing = {"(": ")", "{": "}", "[": "]"}
        for s in string:
            if s in list(closing.keys()):
                st.append(s)
                continue

            if len(st) != 0 and closing[st[-1]] == s:
                st.pop()
            else:
                return False
        return len(st) == 0


if __name__ == "__main__":
    import lc

    lc.test(Solution)
