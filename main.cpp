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
    map<int, int> speakers;
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        speakers[x]++;
    }
    int m;
    cin >> m;
    int ca[m], cs[m];
    for (int i = 0; i < m; i++) {
        scanf("%d", &ca[i]);
    }
    int answer = 0;
    pair answer_pair = {0, 0};
    for (int i = 0; i < m; i++) {
        int sub;
        scanf("%d", &sub);
        const pair curr = {speakers[ca[i]], speakers[sub]};
        if (curr.first > answer_pair.first || (
                curr.first == answer_pair.first && curr.second > answer_pair.second)) {
            answer_pair = curr;
            answer = i;
        }
    }
    cout << answer + 1 << endl;
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
