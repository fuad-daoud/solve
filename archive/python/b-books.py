def cin(line):
    return list(map(int, line.strip().split()))

dx = [-1, 1, 0, 0]
dy = [0, 0, -1, 1]



def main():

    n, k = cin(input())

    numbers = cin(input())
    pointer = 0
    sum = 0
    answer = 0

    for i in range(n):
        while(pointer < n and sum + numbers[pointer] <= k):
            sum += numbers[pointer]
            pointer += 1
        answer = max(answer, pointer - i)
        sum -= numbers[i]


    print(answer)
    return
    # test(solve([[1, 6], [2, 4], [4, 8], [3, 6]], 4), ([1, 0, 0, 0], [0, 1, 0, 1]))
    # test(solve([[1, 1000000000], [2, 1000000000]], 2), ([1, 0], [0, 1]))


def test(real, expected):
    print("====================test===============")
    # real = sorted(real)
    # expected = sorted(expected)
    print("real: ", real)
    print("expected: ", expected)
    assert expected == expected

if __name__ == '__main__':
    main()
