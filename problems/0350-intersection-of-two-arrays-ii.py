class Solution(object):
    def intersect(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: List[int]
        """

        freq1 = {}
        for num in nums1:
            freq1[num] = freq1.get(num, 0) + 1


        freq2 = {}
        for num in nums2:
            freq2[num] = freq2.get(num, 0) + 1

        answer = []

        for num in freq1:
            if num in freq2:
                freq = min(freq1[num], freq2[num])
                answer += [num] * freq
        return answer

