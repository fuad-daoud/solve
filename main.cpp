#include <algorithm>
#include <vector>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits.h>
#include <map>
#include <numeric>
#include <set>
#include <stack>
#include <stdio.h>

#ifndef ONLINE_JUDGE
#include "util.h"
#endif

using namespace ::std;

int dx[4] = {0, 0, 1, -1}; // Up, Down, Right, Left
int dy[4] = {-1, 1, 0, 0}; // Up, Down, Right, Left

const int N = 2e5 + 1, M = 48, mod = 1e9 + 7;
#define in(i, j) i >= 0 && i < j
#define not_in(i, j) !(in(i, j))
int n, m;
// string grid[N];
// int dp[N][N];
char chars[] = {'a', 'b', 'c'};

void solve() {
    int n, m;
    cin >> n >> m;
    string grid[n];
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }
    int answer = 0;
    bool removed[m];
    memset(removed, false, m);
    for (int col = 0; col < m; col++) {
        for (int row = 1; row < n; row++) {
            if (grid[row - 1][col] > grid[row][col]) {
                bool invalid = false;
                for (int previous_col = 0; previous_col < col; previous_col++) {
                    if (removed[previous_col]) {
                        continue;
                    }
                    if (grid[row - 1][previous_col] < grid[row][previous_col]) {
                        invalid = true;
                        break;
                    }

                }
                if (invalid) {
                    continue;
                }
                answer++;
                removed[col] = true;
                break;
            }
        }
    }
    cout << answer << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    assert(freopen("input.txt", "rt", stdin));
    // freopen("output.txt", "w", stdout);
#endif
    int cases = 1;
    // cin >> cases;
    while (cases--) {
        solve();
    }
    return 0;
}
