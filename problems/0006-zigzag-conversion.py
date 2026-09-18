class Solution(object):
    def convert(self, s, numRows):
        """
        :type s: str
        :type numRows: int
        :rtype: str
        """
        if numRows == 1 or numRows >= len(s):
            return s
        rows = [''] * numRows
        cycle = 2 * numRows - 2
        for i in range(len(s)):
            pos = i % cycle
            if pos < numRows:
                rows[pos] += s[i]
            else:
                rows[cycle - pos] += s[i]
        return ''.join(rows)

