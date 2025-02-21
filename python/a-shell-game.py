def cin(): return list(map(int, input().strip().split()))

def main():

    with open("input.txt", "r") as f:
        bal = int(f.readline())


        for _ in range(3):
            shuff = list(map(int, f.readline().strip().split()));
            if bal == shuff[0]:
                bal = shuff[1]
            elif bal == shuff[1]:
                bal = shuff[0]

        with open("output.txt", "w") as fw:
            fw.write(str(bal))


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
