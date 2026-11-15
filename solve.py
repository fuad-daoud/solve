# 155. Min Stack [Medium]
# https://leetcode.com/problems/min-stack/


class MinStack:
    def __init__(self):
        self.st = []
        self.mns = []

    def push(self, value: int) -> None:
        self.st.append(value)
        if len(self.mns) == 0:
            self.mns.append(value)
        else:
            self.mns.append(min(self.mns[-1], value))

    def pop(self) -> None:
        self.st.pop()
        self.mns.pop()

    def top(self) -> int:
        return self.st[-1]

    def getMin(self) -> int:
        return self.mns[-1]


if __name__ == "__main__":
    import lc

    lc.test(MinStack)
