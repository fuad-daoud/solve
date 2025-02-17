class Solution(object):
    def maxProfit(self, prices):
        """
        :type prices: List[int]
        :rtype: int
        """
        if len(prices) == 0:
            return 0
        answer = 0
        for index in range(0, len(prices) - 1):
            if prices[index] < prices[index + 1]:
                answer += prices[index + 1] - prices[index]
        return answer
