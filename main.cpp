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
char chars[] = {'a', 'b', 'c'};

void solve() {
    int n, k;
    cin >> n >> k;
    int arr[n];
    set<int> big_dawgs;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        if (arr[i] > n - k) {
            big_dawgs.insert(i);
        }
    }
    const long long MOD = 998244353;
    long long answer = 1;
    long long count = 0;
    bool counting = false;
    for (int i = 0; i < n; i++) {
        if (big_dawgs.count(i) == 1) {
            counting = true;
            if (count != 0) {
                answer = (answer * count) % MOD;
                count = 0;
            }
        }
        if (counting) {
            count++;
        }
    }
    long long sum = 0;
    for (int i = n - k + 1; i <= n; i++) {
        sum += i;
    }
    cout << sum << ' ' << answer << endl;
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