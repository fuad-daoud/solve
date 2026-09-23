# 20. Valid Parentheses [Easy]
# https://leetcode.com/problems/valid-parentheses/


class Solution:
    def isValid(self, s: str) -> bool:
        st = []
        for c in s:
            if not st and (c == ")" or c == "]" or c == "}"):
                return False
            if c == ")" and st[-1] == "(":
                st.pop()
                continue

            if c == "]" and st[-1] == "[":
                st.pop()
                continue

            if c == "}" and st[-1] == "{":
                st.pop()
                continue

            st.append(c)

        return not st


if __name__ == "__main__":
    import lc

    lc.test(Solution)
