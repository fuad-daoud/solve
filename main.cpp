#include <algorithm>
#include <bitset>
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
#include <queue>
#include <set>
#include <stack>
#include <stdio.h>
#include <unordered_map>

#ifndef ONLINE_JUDGE
#include "util.h"
#endif

using namespace ::std;

int dx[4] = {0, 0, 1, -1}; // Up, Down, Right, Left
int dy[4] = {-1, 1, 0, 0}; // Up, Down, Right, Left

// const int N = 3 * 1e4 + 7, M = 250, mod = 1e9 + 7;
#define in(i, j) i >= 0 && i < j
#define not_in(i, j) !(in(i, j))
// int n, l, m;
// string grid[N];
// int dp[N][N];

void solve() {
    int n;
    cin >> n;
    int sizes[n], costs[n];
    for (int i = 0; i < n; i++) {
        cin >> sizes[i];
    }

    for (int i = 0; i < n; i++) {
        cin >> costs[i];
    }

    long long mins[n];

    for (int i = n - 2; i >= 0; i--) {
        const int current = sizes[i];
        int mn = INT_MAX;
        for (int j = i + 1; j < n; j++) {
            if (current < sizes[j]) {
                mn = min(mn, costs[j]);
            }
        }
        mins[i] = mn;
    }
    long long answer = INT_MAX;
    for (int i = 0; i < n; i++) {
        const int current = sizes[i];
        for (int j = i + 1; j < n; j++) {
            if (current < sizes[j]) {
                answer = min(answer, costs[i] + costs[j] + mins[j]);
            }
        }
    }
    if (answer == INT_MAX) {
        cout << -1 << endl;
        return;
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
