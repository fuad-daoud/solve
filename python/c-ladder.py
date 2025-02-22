def cin(line):
    return list(map(int, line.strip().split()))

dx = [-1, 1, 0, 0]
dy = [0, 0, -1, 1]



def main():

    # f = open("input.txt", "r")
    n, q = cin(input())

    numbers = cin(input())

    ranges = []

    for i in range(n - 1):
        if numbers[i] < numbers[i + 1]:
            ranges.append(("up", 0))
        elif numbers[i] > numbers[i + 1]:
            ranges.append(("down", 0))
        else:
            ranges.append(("flat", 0))

    if n > 1:
        for i in range(len(ranges) - 2, -1, -1):
            if ranges[i + 1][0] == ranges[i][0]:
                ranges[i] = (ranges[i][0], ranges[i + 1][1] + 1)


    for i in range(q):
        l, r = cin(input())
        l -= 1
        r -= 1
        r -= 1

        if l == r:
            print("Yes")
            continue
        seenDown = False
        if l == n - 1:
            print("Yes")
            continue
        if ranges[l][0] == "down":
            seenDown = True

        answer = "Yes"
        while l <= r:
            if ranges[l][0] == "up" and seenDown:
                answer = "No"
                break
            if ranges[l][0] == "down":
                seenDown = True
            l += ranges[l][1] + 1
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
