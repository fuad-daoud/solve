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
    int n, k;
    cin >> n >> k;
    priority_queue<int> answer;
    while (n) {
        int x = pow(2,floor(log2(n)));
        answer.emplace(x);
        n -= x;
    }
    k -= answer.size();
    while (k > 0) {
        const int x = answer.top();
        if (x == 1) {
            break;
        }
        answer.pop();
        answer.emplace(x / 2);
        answer.emplace(x / 2);
        k--;
    }
    if (k == 0) {
        cout << "YES" << endl;
    } else {
       cout << "NO" << endl;
        return;
    }
    while (!answer.empty()) {
        cout << answer.top() << ' ';
        answer.pop();
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
