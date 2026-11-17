# 121. Best Time to Buy and Sell Stock [Easy]
# https://leetcode.com/problems/best-time-to-buy-and-sell-stock/


class Solution:
    def maxProfit(self, prices: list[int]) -> int:
        answer = -1
        mx = -1
        for p in reversed(prices):
            answer = max(answer, mx - p)
            mx = max(mx, p)

        return max(0, answer)


if __name__ == "__main__":
    import lc

    lc.test(Solution)
