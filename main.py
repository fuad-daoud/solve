from python import three_sum


def cin(): return map(int, input().strip().split())

def main():
    solution  = three_sum.Solution()
    test(solution.threeSum([-1,0,1,2,-1,-4]), [[-1,-1,2],[-1,0,1]])
    test(solution.threeSum([0,1,1]), [])
    test(solution.threeSum([0,0,0]), [[0,0,0]])
    test(solution.threeSum([0,0,0,0]), [[0,0,0]])



def test(real, expected):
    print("====================test===============")
    real = sorted(real)
    expected = sorted(expected)
    print("real: ", real)
    print("expected: ", expected)
    assert expected == expected

if __name__ == '__main__':
    main()
