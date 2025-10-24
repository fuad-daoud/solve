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
    int m, t, r;
    cin >> m >> t >> r;
    int after_midnight[601] = {};
    int before_midnight[601] = {};
    int ghosts[m];
    for (int i = 0; i < m; i++) {
        cin >> ghosts[i];
    }
    for (int ghost: ghosts) {
        int count = 0;
        for (int i = ghost - t; i < ghost; i++) {
            if (i < 0) {
                count += before_midnight[i * -1];
                continue;
            }
            count += after_midnight[i];
        }
        for (int i = ghost - 1; i >= ghost - t; i--) {
            if (count >= r) {
                break;
            }
            if (i < 0) {
                if (before_midnight[i * -1] == 0) {
                    before_midnight[i * -1]++;
                    count++;
                }
                continue;
            }
            if (after_midnight[i] == 0) {
                count++;
                after_midnight[i]++;
            }
        }
        if (count < r) {
            cout << -1 << endl;
            return;
        }
    }
    int answer = 0;

    for (const int i: before_midnight) {
        answer += i;
    }
    for (const int i: after_midnight) {
        answer += i;
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
