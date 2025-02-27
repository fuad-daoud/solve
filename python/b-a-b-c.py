def cin(line):
    return list(map(int, line.strip().split()))

dx = [-1, 1, 0, 0]
dy = [0, 0, -1, 1]



def main():

    # f = open("input.txt", "r")
    s = input()
    n = len(s)
    answer = 0
    for i in range(n):
        for j in range(i + 1, n):
            for k in range(j + 1, n):
                if j - i == k - j and s[i] == 'A' and s[j] == 'B' and s[k] == 'C':
                    answer += 1
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
