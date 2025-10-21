#include <algorithm>
#include <vector>
#include <cassert>
#include <cmath>
#include <cstdio>
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

int jump(int current, const int previous_step) {
    if (current > farthest_gem) {
        return 0;
    }
    const int indexed_step = previous_step - (l - 250);
    if (visited[current][indexed_step]) {
        return dp[current][indexed_step];
    }
    visited[current][indexed_step] = true;
    if (previous_step == 1) {
        return dp[current][indexed_step] = gems[current] + max(jump(current + previous_step, previous_step),
                                                               jump(current + previous_step, previous_step + 1));
    }

    return dp[current][indexed_step] = gems[current] + max(jump(current + previous_step, previous_step - 1), max(
                                                               jump(current + previous_step, previous_step),
                                                               jump(current + previous_step, previous_step + 1)));
}


void solve() {
    cin >> n >> l;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        farthest_gem = max(farthest_gem, x);
        gems[x]++;
    }
    dp[0][l] = jump(0, l);
    cout << dp[0][l] << endl;
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
