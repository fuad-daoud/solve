# 739. Daily Temperatures [Medium]
# https://leetcode.com/problems/daily-temperatures/


class Solution:
    def dailyTemperatures(self, temperatures: list[int]) -> list[int]:
        answer = []
        stack = []
        n = len(temperatures)
        for i, t in enumerate(reversed(temperatures)):
            i = n - i - 1
            if len(stack) == 0:
                stack.append([t, i])
                answer.append(0)
                continue

            while len(stack) != 0 and t >= stack[-1][0]:
                stack.pop()

            if len(stack) == 0:
                stack.append([t, i])
                answer.append(0)
                continue

            answer.append(stack[-1][1] - i)
            stack.append([t, i])

        return answer[::-1]


if __name__ == "__main__":
    import lc

    lc.test(Solution)
