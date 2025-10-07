#include <algorithm>
#include <vector>
#include <cassert>
#include <cstdio>
#include <iostream>
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
    int m, s;
    cin >> m >> s;
    if (s == 0) {
        if (m == 1) {
            cout << "0 0" << endl;
            return;
        }
        cout << "-1 -1" << endl;
        return;
    }
    if (m * 9 < s) {
        cout << "-1 -1" << endl;
        return;
    }

    if (m == 1) {
        cout << s << " " << s << endl;
        return;
    }
    string maximos;
    while (s > 0) {
        const int current = min(9, s);
        maximos += to_string(current);
        s -= current;
    }
    string minimos = maximos;
    reverse(minimos.begin(), minimos.end());
    if (minimos.size() < m) {
        minimos[0]--;
    }
    while (maximos.size() < m) {
        maximos += "0";
    }
    while (minimos.size() < m - 1) {
        minimos.insert(0, "0");
    }

    if (minimos.size() < m) {
        minimos.insert(0, "1");
    }
    cout << minimos << " " << maximos << endl;
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
