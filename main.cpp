#include <algorithm>
#include <vector>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <set>
#include <stdio.h>

#ifndef ONLINE_JUDGE
#include "util.h"
#endif

using namespace ::std;

int dx[4] = {0, 0, 1, -1}; // Up, Down, Right, Left
int dy[4] = {-1, 1, 0, 0}; // Up, Down, Right, Left

// const int N = 1e4 + 1, M = 48, mod = 1e9 + 7;
#define in(i, j) i >= 0 && i < j
#define not_in(i, j) !(in(i, j))
int n, m;
// string grid[N];
// int dp[N][N];
char chars[] = {'a', 'b', 'c'};


void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> intersections[n + 1];
    vector<vector<bool>> ok(n + 1, vector<bool>(n + 1, false));
    for (int i = 0; i < m; i++) {
        int nodeA, nodeB;
        cin >> nodeA >> nodeB;
        ok[nodeA][nodeB] = true;
        intersections[nodeA].emplace_back(nodeB);
    }

    int answer = 0;
    for (int a = 1; a <= n; a++) {
        for (int d = 1; d <= n; d++) {
            if (d == a) {
                continue;
            }
            int r = 0;
            // count is d valid and count the intersections that lead to (d) from (a) being b
            for (const int b: intersections[a]) {
                if (b == d) {
                    continue;
                }
                if (ok[b][d]) {
                    r++;
                }
            }
            answer += r * (r - 1) / 2;
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
