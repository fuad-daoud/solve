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

const int N = 2e5 + 1, M = 48, mod = 1e9 + 7;
#define in(i, j) i >= 0 && i < j
#define not_in(i, j) !(in(i, j))
int n, m;
// string grid[N];
// int dp[N][N];
char chars[] = {'a', 'b', 'c'};

void solve() {
    int n;
    cin >> n;
    int serves[n];
    for (int i = 0; i < n; i++) {
        cin >> serves[i];
    }
    vector<int> indices_a, indices_b;
    indices_a.emplace_back(-1);
    indices_b.emplace_back(-1);
    for (int i = 0; i < n; i++) {
        if (serves[i] == 1) {
            indices_a.emplace_back(i);
        }
        if (serves[i] == 2) {
            indices_b.emplace_back(i);
        }
    }

    int c_a[n + 1], c_b[n + 1], index_a = 0, index_b = 0;
    memset(c_a, 0, (n + 1) * sizeof(int));
    memset(c_b, 0, (n + 1) * sizeof(int));
    for (int i = 0; i < n; i++) {
        if (serves[i] == 1) {
            c_a[i] = ++index_a;
            c_b[i] = index_b;
        }
        if (serves[i] == 2) {
            c_b[i] = ++index_b;
            c_a[i] = index_a;
        }
    }

    vector<pair<int, int> > answer;
    for (int t = 1; t <= n; t++) {
        int sets_a = 0, sets_b = 0;
        int index_a = 0, index_b = 0, previous_a = 0, previous_b = 0;
        int consumed_serves = 0, last_to_win = -1;
        while (index_a < n || index_b < n) {
            index_a = t + previous_a >= indices_a.size() ? INT_MAX : indices_a[t + previous_a];
            index_b = t + previous_b >= indices_b.size() ? INT_MAX : indices_b[t + previous_b];
            if (index_a == INT_MAX && index_b == INT_MAX) {
                break;
            }
            if (index_a < index_b) {
                sets_a++;
                consumed_serves = index_a;
                last_to_win = 1;
            } else if (index_b < index_a) {
                sets_b++;
                consumed_serves = index_b;
                last_to_win = 2;
            }
            index_a = min(index_b, index_a);
            index_b = index_a;
            previous_a = c_a[index_a];
            previous_b = c_b[index_b];
        }
        if (sets_a == sets_b || consumed_serves != n - 1) {
            continue;
        }
        if (sets_a > sets_b && last_to_win == 2 || sets_b > sets_a && last_to_win == 1) {
            continue;
        }
        answer.emplace_back(max(sets_a, sets_b), t);
    }
    cout << answer.size() << endl;
    sort(answer.begin(), answer.end());
    for (auto p: answer) {
        cout << p.first << ' ' << p.second << endl;
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
