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
    string s;
    cin >> s;
    bool not_valid[s.size()];
    memset(not_valid, false, s.size());
    // We will assume that three identical letters together is a typo
    // Besides, a couple of identical letters immediately followed by another couple of identical letters is a typo too
    vector<int> dups;
    dups.emplace_back(1);
    for (int i = 1; i < s.size(); i++) {
        if (s[i] == s[i - 1]) {
            dups.back()++;
        } else {
            dups.emplace_back(1);
        }
        if (dups.back() > 2) {
            not_valid[i] = true;
            dups.back()--;
        } else if (dups.size() > 1 && dups.back() == 2 && dups[dups.size() - 2] == 2) {
            not_valid[i] = true;
            dups.back()--;
        }
    }
    for (int i = 0; i < s.size(); i++) {
        if (not_valid[i]) {
            continue;
        }
        cout << s[i];
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
