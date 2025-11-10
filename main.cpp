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


int convert(int x) {
    string binaryString;
    while (x > 0) {
        binaryString += (x % 2 == 0 ? '0' : '1');
        x /= 2;
    }
    reverse(binaryString.begin(), binaryString.end());
    return stoi(binaryString);
}

void solve() {
    int n, x, y;
    cin >> n >> x >> y;
    if (x > y) {
        cout << n << endl;
        return;
    }
    int lesser = 0;
    for (int i = 0; i < n; i++) {
        int door;
        cin >> door;
        lesser += door <= x;
    }
    cout << (lesser + 1) / 2 << endl;
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
