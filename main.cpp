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
#include <stack>
#include <stdio.h>

#ifndef ONLINE_JUDGE
#include "util.h"
#endif

using namespace ::std;

int dx[4] = {0, 0, 1, -1}; // Up, Down, Right, Left
int dy[4] = {-1, 1, 0, 0}; // Up, Down, Right, Left

const int N = 3 * 1e4 + 7, M = 250, mod = 1e9 + 7;
#define in(i, j) i >= 0 && i < j
#define not_in(i, j) !(in(i, j))
int n, l, m;
// string grid[N];
// int dp[N][N];
char chars[] = {'a', 'b', 'c'};


int gems[N] = {};
int farthest_gem = INT_MIN;
int dp[N][500];
bool visited[N][500];


void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    bool grid[n + 2][m + 2];
    for (int i = 0; i < n + 2; i++) {
        for (int j = 0; j < m + 2; j++) {
            grid[i][j] = false;
        }
    }
    int answer = 0;
    for (int i = 0; i < k; i++) {
        int x, y;
        cin >> x >> y;
        grid[x][y] = true;
        if (answer == 0) {
            if (grid[x][y] && grid[x + 1][y] && grid[x][y + 1] && grid[x + 1][y + 1]) {
                answer = i + 1;
            }
            if (grid[x][y] && grid[x + 1][y] && grid[x][y - 1] && grid[x + 1][y - 1]) {
                answer = i + 1;
            }
            if (grid[x][y] && grid[x - 1][y] && grid[x][y - 1] && grid[x - 1][y - 1]) {
                answer = i + 1;
            }
            if (grid[x][y] && grid[x - 1][y] && grid[x][y + 1] && grid[x - 1][y + 1]) {
                answer = i + 1;
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
