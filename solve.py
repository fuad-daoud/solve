# 875. Koko Eating Bananas [Medium]
# https://leetcode.com/problems/koko-eating-bananas/


import math


class Solution:
    def minEatingSpeed(self, piles: list[int], h: int) -> int:
        lo = 1
        hi = best = max(piles)
        while lo <= hi:
            rate = (lo + hi) // 2
            tmp = h
            for p in piles:
                if tmp < 0:
                    break
                tmp -= math.ceil(p / rate)
            if tmp >= 0:
                best = min(best, rate)
                hi = rate - 1
            else:
                lo = rate + 1

        return best


if __name__ == "__main__":
    import lc

    lc.test(Solution)
