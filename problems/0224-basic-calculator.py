# 224. Basic Calculator [Hard]
# https://leetcode.com/problems/basic-calculator/


class Solution:
    def calculate(self, string: str) -> int:
        st = []
        string = string.replace(" ", "")
        skip = set()
        for i, s in enumerate(string):
            # print("start", i, s, st, skip)
            if i in skip:
                continue
            if s == ")":
                # pop the opening parentheses and calculate
                st.pop(-2)
                s = st.pop()

                if len(st) != 0 and (st[-1] == "-" or st[-1] == "+"):
                    sign = st.pop()
                    if sign == "-":
                        s *= -1
                if len(st) != 0 and st[-1] != "(":
                    st.append(int(s) + int(st.pop()))
                else:
                    st.append(s)
                continue
            if s == "(":
                st.append(s)
                continue
            if s == "-" or s == "+":
                st.append(s)
                continue

            if i < len(string) - 1:
                original = i
                i += 1
                while i < len(string) and string[i].isnumeric():
                    skip.add(i)
                    i += 1
                s = convert(string[original:i])
            s = int(s)
            if len(st) != 0 and (st[-1] == "-" or st[-1] == "+"):
                sign = st.pop()
                if sign == "-":
                    s *= -1

            if len(st) != 0 and st[-1] != "(":
                st.append(s + int(st.pop()))
            else:
                st.append(s)

        return st.pop()


def convert(string):
    result = 0
    string = reversed(string)
    for i, s in enumerate(string):
        result += int(s) * pow(10, i)
    return result


if __name__ == "__main__":
    import lc

    lc.test(Solution)
