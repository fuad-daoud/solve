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
    int n, m;
    cin >> n;
    int boys[102] = {};
    for (int i = 0; i < n; i++) {
        int boy;
        cin >> boy;
        boys[boy]++;
    }
    cin >> m;
    int gals[102] = {};

    for (int i = 0; i < m; i++) {
        int gal;
        cin >> gal;
        gals[gal]++;
    }
    int answer = 0;
    for (int i = 1; i < 101; i++) {
        for (int j = i - 1; j < i + 2; j++) {
            const int current = min(gals[j], boys[i]);
            if (current == 0) {
                continue;
            }
            gals[j] -= current;
            boys[i] -= current;
            answer += current;
        }

        for (int j = i - 1; j < i + 2; j++) {
            const int current = min(gals[i], boys[j]);
            if (current == 0) {
                continue;
            }
            gals[i] -= current;
            boys[j] -= current;
            answer += current;
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
