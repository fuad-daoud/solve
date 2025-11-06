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

const int N = 3 * 1e4 + 7, M = 250, mod = 1e9 + 7;
#define in(i, j) i >= 0 && i < j
#define not_in(i, j) !(in(i, j))
int n, l, m;
// string grid[N];
// int dp[N][N];
char chars[] = {'a', 'b', 'c'};


void solve() {
    int n;
    cin >> n;
    pair<int, int> in[n];
    for (int i = 0; i < n; i++) {
        cin >> in[i].first;
    }

    for (int i = 0; i < n; i++) {
        cin >> in[i].second;
    }
    int diff[n];
    for (int i = 0; i < n; i++) {
        diff[i] = in[i].first - in[i].second;
    }
    sort(diff, diff + n);
    long long answer = 0;
    for (int i = 0; i < n - 1; i++) {
        int target = -diff[i] + 1;
        const int *comp = lower_bound(diff + i + 1, diff + n, target);
        answer += n - (comp - diff);
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
