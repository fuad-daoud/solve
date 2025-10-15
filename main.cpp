#include <algorithm>
#include <vector>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
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
    int all_values[2 * N];
    int n, m, k = 0;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        all_values[k++] = a[i];
    }
    cin >> m;
    int b[m];
    for (int i = 0; i < m; i++) {
        cin >> b[i];
        all_values[k++] = b[i];
    }
    sort(a, a + n);
    sort(b, b + m);
    pair answer(3 * n, 3 * m);
    for (int i = 0; i < k; i++) {
        int a_position = upper_bound(a, a + n, all_values[i]) - a;
        int b_position = upper_bound(b, b + m, all_values[i]) - b;
        int a_score = a_position * 2 + (n - a_position) * 3;
        int b_score = b_position * 2 + (m - b_position) * 3;
        int current_score = answer.first - answer.second;
        int new_score = a_score - b_score;
        if (new_score == current_score) {
            answer = max(answer, {a_score, b_score});
        } else if (new_score > current_score) {
            answer = {a_score, b_score};
        }
    }
    cout << answer.first << ":" << answer.second << endl;
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
