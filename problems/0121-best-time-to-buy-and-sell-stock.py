# 121. Best Time to Buy and Sell Stock [Easy]
# https://leetcode.com/problems/best-time-to-buy-and-sell-stock/


# Kadane's algorithmKadane's algorithm


class Solution:
    def maxProfit(self, prices: list[int]) -> int:
        answer = 0
        sm = 0
        for i in range(0, len(prices) - 1):
            if i == len(prices) - 1:
                break
            d = prices[i + 1] - prices[i]
            if sm < 0:
                sm = d
            else:
                sm += d
            answer = max(answer, sm)

        return answer


if __name__ == "__main__":
    import lc

    lc.test(Solution)
