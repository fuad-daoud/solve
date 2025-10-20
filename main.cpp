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

const int N = 1050, M = 48, mod = 1e9 + 7;
#define in(i, j) i >= 0 && i < j
#define not_in(i, j) !(in(i, j))
int n, m;
// string grid[N];
// int dp[N][N];
char chars[] = {'a', 'b', 'c'};


int group[N] = {};

int find_group(int x) {
    if (x == group[x]) {
        return x;
    }
    return group[x] = find_group(group[x]);
}

void solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        group[i] = i;
    }
    int a[n + 1];
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            char x;
            cin >> x;
            if (x == '0') {
                continue;
            }

            const int group_a = find_group(i);
            const int group_b = find_group(j);
            if (group_a != group_b) {
                group[group_a] = group_b;
            }
        }
    }

    vector<int> positions[N] = {};
    for (int i = 1; i <= n; i++) {
        positions[find_group(i)].emplace_back(a[i]);
    }
    for (int i = 1; i <= n; i++) {
        sort(positions[i].begin(), positions[i].end());
    }
    int counter[N] = {};
    for (int i = 1; i <= n; i++) {
        int g = find_group(i);
        int answer = positions[g][counter[g]++];
        cout << answer << ' ';
    }
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
