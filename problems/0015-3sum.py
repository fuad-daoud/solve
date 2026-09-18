from typing import List


class Solution(object):
    def threeSum(self, nums:List[int]):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        nums = sorted(nums)
        print(nums)
        answer = []
        for i in range(len(nums)):
            if nums[i] > 0:
                break
            if i == 0 or nums[i - 1] != nums[i]:
                twoSum(nums, i, answer)

        return answer

def twoSum(nums, i, answer):
    seen = set()
    j = i + 1
    while j < len(nums):
        target = (nums[i] + nums[j]) * -1
        if target in seen:
            answer += [[nums[i], nums[j], target]]
            while j + 1 < len(nums) and nums[j] == nums[j + 1]:
               j += 1
        seen.add(nums[j])
        j += 1
    return 0
