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

// const int N = 3 * 1e4 + 7, M = 250, mod = 1e9 + 7;
#define in(i, j) i >= 0 && i < j
#define not_in(i, j) !(in(i, j))
// int n, l, m;
// string grid[N];
// int dp[N][N];


void solve() {
    int n, m;
    cin >> n >> m;
    if (m > 2 * n + 2) {
        cout << -1 << endl;
        return;
    }
    if (m < n - 1) {
        cout << -1 << endl;
        return;
    }

    if (m == n) {
        for (int i = 0; i < n; i++) {
            cout << "01";
        }
        return;
    }
    if (m == n - 1) {
        cout << "0";
        for (int i = 0; i < m; i++) {
            cout << "10";
        }
        return;
    }
    if (m > n) {
        bool ones = false;
        while (m > n) {
            cout << "11";
            m -= 2;
            if (m == n) {
                ones = true;
                break;
            }
            cout << "0";
            n--;
        }
        if (ones) {
            for (int i = 0; i < m; i++) {
                cout << "01";
            }
        } else {
            for (int i = 0; i < m; i++) {
                cout << "10";
            }
        }
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
