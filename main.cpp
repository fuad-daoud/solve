#include <algorithm>
#include <vector>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <set>
#include <stack>
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
    int n;
    cin >> n;
    stack<int> teams[3];
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        x--;
        teams[x].push(i + 1);
    }

    cout << min(teams[0].size(), min(teams[1].size(), teams[2].size())) << endl;
    while (true) {
        for (const auto & team : teams) {
            if (team.empty()) {
                return;
            }
        }

        for (auto & team : teams) {
            cout << team.top() << " ";
            team.pop();
        }
        cout << endl;
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
