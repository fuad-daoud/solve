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
    int n;
    cin >> n;
    int numbers[n];
    for (int i = 0; i < n; i++) {
        cin >> numbers[i];
    }
    sort(numbers, numbers + n);
    int last = -1;
    bool vis[n];
    memset(vis, false, sizeof(false) * n);
    vector<int> answer1;

    for (int i = 0; i < n; i++) {
        if (last != numbers[i]) {
            answer1.emplace_back(numbers[i]);
            vis[i] = true;
            last = answer1.back();
        }
    }

    vector<int> answer2;
    for (int i = 0; i < n; i++) {
        if (vis[i]) {
            continue;
        }
        if (last != numbers[i]) {
            answer2.emplace_back(numbers[i]);
            vis[i] = true;
            last = answer2.back();
        }
    }
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            cout << "NO" << endl;
            return;
        }
    }
    cout << "YES" << endl;
    cout << answer2.size() << endl;
    for (const int x : answer2) {
        cout << x << ' ';
    }
    cout << endl;
    cout << answer1.size() << endl;
    reverse(answer1.begin(), answer1.end());
    for (const int x : answer1) {
        cout << x << ' ';
    }
    cout << endl;;
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
