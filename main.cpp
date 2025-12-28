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

void solve() {
    int n;
    cin >> n;
    while (n--) {
        int c, m, x;
        cin >> c >> m >> x;
        int answer = 0;
        if (c == 0 || m == 0) {
            cout << answer << endl;
            continue;
        }
        if (x != 0) {
            answer += min(min(c, m), x);
            c -= answer;
            m -= answer;
        }

        if (c == 0 || m == 0) {
            cout << answer << endl;
            continue;
        }
        if (c != m) {
            const int diff = min(min(m,abs(c - m)), c);
            answer += diff;
            if (c > m) {
                c -= 2 * diff;
                m -= diff;
            } else {
                m -= 2 * diff;
                c -= diff;
            }
        }
        if (c == m) {
            answer += (c + m) / 3;
        }
        cout << answer << endl;;
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
