
def cin(line):
    return list(map(int, line.strip().split()))

dx = [-1, 1, 0, 0]
dy = [0, 0, -1, 1]



def main():
    # input
    ops = []
    for _ in range(3):
        op = input().strip().split()[0]
        op = list(op)
        if op[1] == "<":
            op[0], op[1], op[2] = op[2], ">", op[0]
        ops.append(op)


    # filling comparism table
    answer = {'A':0, 'B':0, 'C':0}
    for i in range(3):
        op = ops[i]
        answer[op[0]] = answer[op[0]] + 1
        answer[op[2]] = answer[op[2]] - 1

    # checking if valid
    if sorted(answer.values()) != [-2, 0, 2]:
        print("Impossible")
        return

    # printing the answer
    for key in answer.keys():
        if answer[key] == -2:
            print(key, end="")

    for key in answer.keys():
        if answer[key] == 0:
            print(key, end="")

    for key in answer.keys():
        if answer[key] == 2:
            print(key, end="\n")

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
