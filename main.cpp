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
    string s;
    cin >> s;
    string answer = "";
    for (int i = 0; i < n; i++) {
        switch (s[i]) {
            case '0':
            case '1':
                break;
            case '2':
            case '3':
            case '5':
            case '7':
                answer.push_back(s[i]);
                break;
            case '4':
                answer += "322";
                break;
            case '6':
                answer += "53";
                break;
            case '8':
                answer += "7222";
                break;
            case '9':
                answer += "7332";
                break;
        }
    }
    sort(answer.rbegin(), answer.rend());
    cout << answer << endl;
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
