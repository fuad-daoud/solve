# 155. Min Stack [Medium]
# https://leetcode.com/problems/min-stack/

import heapq


class MinStack:
    def __init__(self):
        self.st = []
        self.q = []
        self.freq = {}

    def push(self, value: int) -> None:
        heapq.heappush(self.q, value)
        self.freq[value] = self.freq.get(value, 0) + 1
        self.st.append(value)

    def pop(self) -> None:
        value = self.st.pop()
        self.freq[value] = self.freq[value] - 1

    def top(self) -> int:
        return self.st[-1]

    def getMin(self) -> int:
        while self.freq[self.q[0]] == 0:
            heapq.heappop(self.q)
        return self.q[0]


if __name__ == "__main__":
    import lc

    lc.test(MinStack)
