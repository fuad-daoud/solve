def cin(line):
    return list(map(int, line.strip().split()))

dx = [-1, 1, 0, 0]
dy = [0, 0, -1, 1]



def main():

    # f = open("input.txt", "r")
    n = int(input())
    for _ in range(n):
        [x, k] = cin(input())
        if x % 2 == 0:
            x += 2 * k
        else:
            x += x
            k -= 1
            x += k * 2
        print(x)


if __name__ == '__main__':
    main()
