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


int gems[N] = {};
int farthest_gem = INT_MIN;
int dp[N][500];
bool visited[N][500];


void solve() {
    int n, m;
    cin >> n >> m;
    long long rooms[n];
    for (int i = 0; i < n; i++) {
        cin >> rooms[i];
    }
    long long letters[m];
    for (int i = 0; i < m; i++) {
        cin >> letters[i];
    }

    long long numbering[n];
    numbering[0] = 0;
    for (int i = 1; i < n; i++) {
        numbering[i] = rooms[i - 1] + numbering[i - 1];
    }
    for (int i = 0; i < m; i++) {
        const long index = lower_bound(numbering, numbering + n, letters[i]) - numbering;
        cout << index << ' ' << letters[i] - numbering[index - 1] << endl;
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
