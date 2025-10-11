#include <algorithm>
#include <vector>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
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
    int n, l;
    cin >> n >> l;
    double lights[n];
    for (int i = 0; i < n; i++) {
        cin >> lights[i];
    }
    double answer = 0;
    sort(lights, lights + n);
    double prev = lights[0];
    answer = max(answer, lights[0]);
    for (int i = 0; i < n; i++) {
        answer = max(answer, (lights[i] - prev) / 2.0);
        prev = lights[i];
    }
    answer = max(answer, (l - prev));
    cout << fixed << setprecision(10) << answer << endl;
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
