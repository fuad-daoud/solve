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
    int n, x;
    cin >> n >> x;
    pair<int, int> times[n];
    int mx = 0;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        times[i] = {a, b};
    }
    sort(times, times + n);
    int cursor = 1, answer = 0;
    for (int i = 0; i < n; i++) {
        int step = (times[i].first - cursor) % x;
        answer += (times[i].second - times[i].first + 1) + step;
        cursor = times[i].second + 1;
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
