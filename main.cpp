#include <algorithm>
#include <bitset>
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
#include <queue>
#include <set>
#include <stack>
#include <stdio.h>
#include <unordered_map>

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
    int n;
    cin >> n;
    map<int, int> freq;
    for (int i = 0; i < n; i++) {
        string x;
        cin >> x;
        int open = 0, close = 0;
        for (const char j: x) {
            if (j == ')') {
                if (open > 0) {
                    open--;
                } else {
                    close++;
                }
            } else {
                open++;
            }
        }
        if (open != 0 && close != 0) {
        } else if (open == 0 && close == 0) {
            freq[0]++;
        } else if (open == 0) {
            freq[close]++;
        } else {
            freq[open * -1]++;
        }
    }
    for (auto const x: freq) {
        if (x.first == 0 || x.second == 0) {
            continue;
        }
        if (freq[x.first * -1] != 0) {
            int y = min(freq[x.first], freq[x.first * -1]);
            freq[x.first] -= y;
            freq[x.first * -1] -= y;
            freq[0] += 2 * y;
        }
    }
    cout << freq[0] / 2 << endl;
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
