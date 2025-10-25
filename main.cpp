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


struct parent_node {
    int r;
    int c;
};

struct node {
    parent_node parent;
    int r;
    int c;
};

void solve() {
    int n, m;
    cin >> n >> m;
    string grid[n];
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }
    vector<pair<int, int> > graph[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char color = grid[i][j];
            if (j + 1 < m && color == grid[i][j + 1]) {
                graph[i][j].emplace_back(i, j + 1);
                graph[i][j + 1].emplace_back(i, j);
            }
            if (i + 1 < n && color == grid[i + 1][j]) {
                graph[i][j].emplace_back(i + 1, j);
                graph[i + 1][j].emplace_back(i, j);
            }
        }
    }
    bool vis[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            vis[i][j] = false;
        }
    }
    stack<node> s;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m - 1; j++) {
            if (vis[i][j]) {
                continue;
            }
            s.emplace(node{parent_node{-1, -1}, i, j});
            while (!s.empty()) {
                auto [parent, r, c] = s.top();
                if (vis[r][c]) {
                    cout << "Yes";
                    return;
                }
                if (parent.r == r && parent.c == c) {
                    continue;
                }
                vis[r][c] = true;
                s.pop();
                for (const auto [row, column]: graph[r][c]) {
                    if (parent.r == row && parent.c == column) {
                        continue;
                    }
                    s.push(node{parent_node{r, c}, row, column});
                }
            }
        }
    }
    cout << "No" << endl;
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
