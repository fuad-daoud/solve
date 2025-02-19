def main():

    n = int(input())

    ranges = []
    for _ in range(n):
        x, y = map(int, input().split())
        ranges.append([x, y])

    contains, contained = solve(ranges, n)
    print(*contains)
    print(*contained)

    # test(solve([[1, 6], [2, 4], [4, 8], [3, 6]], 4), ([1, 0, 0, 0], [0, 1, 0, 1]))
    # test(solve([[1, 1000000000], [2, 1000000000]], 2), ([1, 0], [0, 1]))


def solve(ranges, n):
    indexed_ranges = [(l, r, i) for i, (l, r) in enumerate(ranges)]

    from operator import itemgetter
    indexed_ranges.sort(key=itemgetter(0)) 
    i = 0
    while i < n:
        j = i
        while j < n and indexed_ranges[j][0] == indexed_ranges[i][0]:
            j += 1
        if j - i > 1:
            segment = indexed_ranges[i:j]
            segment.sort(key=itemgetter(1), reverse=True)
            indexed_ranges[i:j] = segment
        i = j

    contained = [0] * n
    contains = [0] * n

    max_right = indexed_ranges[0][1]
    for _, r, i in indexed_ranges[1:]:
        if r <= max_right:
            contained[i] = 1
        max_right = max(max_right, r)

    min_right = indexed_ranges[-1][1]
    for _, r, i in indexed_ranges[-2::-1]:
        if r >= min_right:
            contains[i] = 1
        min_right = min(min_right, r)

    return contains, contained

def test(real, expected):
    print("====================test===============")
    # real = sorted(real)
    # expected = sorted(expected)
    print("real: ", real)
    print("expected: ", expected)
    assert expected == expected

if __name__ == '__main__':
    main()

