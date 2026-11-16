# 150. Evaluate Reverse Polish Notation [Medium]
# https://leetcode.com/problems/evaluate-reverse-polish-notation/

import math


class Solution:
    def evalRPN(self, tokens: list[str]) -> int:
        st = []
        ops = ["*", "/", "-", "+"]
        for t in tokens:
            if t in ops:
                v1 = st.pop()
                v2 = st.pop()
                answer = 0
                if t == "+":
                    answer = v2 + v1
                elif t == "-":
                    answer = v2 - v1
                elif t == "*":
                    answer = v2 * v1
                else:
                    answer = math.trunc(v2 / v1)
                st.append(answer)

                continue
            st.append(int(t))

        return st.pop()


if __name__ == "__main__":
    import lc

    lc.test(Solution)
