class Solution(object):
    def singleNumber(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if len(nums) == 0:
            return 0

        freq = {}

        for num in nums:
            freq[num] = freq.get(num, 0) + 1
        for key in freq:
            if freq[key] == 1:
                return key
        return 0

