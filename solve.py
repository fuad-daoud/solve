# 875. Koko Eating Bananas [Medium]
# https://leetcode.com/problems/koko-eating-bananas/


class Solution:
    def minEatingSpeed(self, piles: list[int], h: int) -> int:
        lo, hi = 1, max(piles)
        while lo < hi:
            k = (lo + hi) // 2
            if sum((p + k - 1) // k for p in piles) <= h:
                hi = k
            else:
                lo = k + 1
        return lo


if __name__ == "__main__":
    import lc

    lc.test(Solution)
