class Solution(object):
    def removeDuplicates(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """

        if len(nums) == 0:
            return nums


        current = nums[0]
        last = 1
        for i in range(1, len(nums)):
            if current != nums[i]:
                current = nums[i]
                nums[last] = nums[i]
                last += 1

        nums = nums[0:last]
        return last
