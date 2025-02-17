class Solution(object):
    def plusOne(self, digits):
        """
        :type digits: List[int]
        :rtype: List[int]
        """
        digits = digits[::-1]
        carry = True
        for i in range(len(digits)):
            digit = digits[i]
            if carry:
                if digit == 9:
                    digits[i] = 0
                    carry = True
                    continue
                digits[i] = digit + 1
                carry = False
            else:
                break
        if carry:
            digits += [1]
        return digits[::-1]

