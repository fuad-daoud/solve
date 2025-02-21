def main():
    with open("input.txt", "r") as f:
        with open("output.txt", "w") as fw:
            n, m, k = list(map(int, f.readline().strip().split()));

            grid = [[False] * (m + 1) for _ in range(n + 1)]
            record = {}

            for _ in range(k):
                tokens = f.readline().strip().split()
                op, x, y ,id = ["", 0, 0, ""]
                if len(tokens) == 2:
                    op, id = list(map(str, tokens));
                else:
                    op, t_x, t_y, id = list(map(str, tokens));
                    x, y = int(t_x), int(t_y)
                if op == "+1":
                    while grid[x][y]:
                        if y == m and x < n:
                            y = 1
                            x += 1
                        elif x == n and y == m:
                            break
                        else:
                            y += 1
                    if not grid[x][y]:
                        record[id] = (x, y)
                        grid[x][y] = True
                elif op == "-1":
                    if id not in record.keys():
                        fw.write(f"-1 -1\n")
                        continue


                    x, y = record[id]
                    grid[x][y] = False
                    del record[id]
                    fw.write(f"{x} {y}\n")

        # with open("output.txt", "w") as fw:
            # fw.write(str(bal))


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

