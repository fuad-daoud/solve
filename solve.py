# 150. Evaluate Reverse Polish Notation [Medium]
# https://leetcode.com/problems/evaluate-reverse-polish-notation/

import operator


class Solution:
    def evalRPN(self, tokens: list[str]) -> int:
        st = []
        OPS = {
            "+": operator.add,
            "-": operator.sub,
            "*": operator.mul,
            "/": lambda a, b: int(a / b),
        }
        for t in tokens:
            if t in OPS:
                right = st.pop()
                left = st.pop()
                st.append(OPS[t](left, right))
                continue
            st.append(int(t))

        return st.pop()


if __name__ == "__main__":
    import lc

    lc.test(Solution)
