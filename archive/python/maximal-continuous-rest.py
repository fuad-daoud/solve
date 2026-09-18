
def cin(): return list(map(int, input().strip().split()))

def main():

    cin()

    hours = cin()
    if 1 not in hours:
        print(0)
        return
    current = 1
    answer = 0
    for i in range(1, len(hours)):
        if hours[i] == hours[i - 1] and hours[i] == 1:
            current += 1
        else:
            current = 1
        if i == len(hours) - 1 and hours[i] == 1 and hours[0] == 1:
            current += 1
            answer = max(answer, current)
            for j in range(1, len(hours)):
                if hours[j] == hours[j - 1] and hours[j] == 1:
                    current += 1
                else:
                    current = 1
                answer = max(answer, current)
        answer = max(answer, current)

    print(answer)
    # test(solution.threeSum([-1,0,1,2,-1,-4]), [[-1,-1,2],[-1,0,1]])
    # test(solution.threeSum([0,1,1]), [])
    # test(solution.threeSum([0,0,0]), [[0,0,0]])
    # test(solution.threeSum([0,0,0,0]), [[0,0,0]])


def test(real, expected):
    print("====================test===============")
    real = sorted(real)
    expected = sorted(expected)
    print("real: ", real)
    print("expected: ", expected)
    assert expected == expected

if __name__ == '__main__':
    main()
