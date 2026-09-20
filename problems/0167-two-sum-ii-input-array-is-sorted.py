# 167. Two Sum II - Input Array Is Sorted [Medium]
# https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/


class Solution:
    def twoSum(self, numbers: list[int], target: int) -> list[int]:
        n = len(numbers)
        for index, number in enumerate(numbers):
            # check for solution where the new other number is number - target, since its already sorted I will use binary search for this
            l, r = 0, n - 1
            other_target = target - number
            while l <= r:
                m_index = (l + r) // 2
                m = numbers[m_index]
                if m == other_target:
                    if other_target == number and index == m_index:
                        if numbers[m_index + 1] == other_target:
                            return [index + 1, m_index + 2]
                        if numbers[m_index - 1] == other_target:
                            return [index + 1, m_index]
                        break
                    return [index + 1, m_index + 1]
                if other_target < m:
                    r = m_index - 1
                if other_target > m:
                    l = m_index + 1

        raise ValueError(
            "It is mentioned in the statement that it is guaranteed that there is exactly one solution"
        )


if __name__ == "__main__":
    import lc

    lc.test(Solution)
