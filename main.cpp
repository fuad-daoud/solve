#include <algorithm>
#include <vector>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <limits.h>
#include <map>
#include <numeric>
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
    int k;
    cin >> n >> k;
    pair<int, int> ins[n];
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        ins[i] = {x, i};
    }
    vector<int> answer;
    sort(ins, ins + n);
    for (int i = 0; i < n; i++) {
        if (ins[i].first > k) {
            break;
        }
        k -= ins[i].first;
        answer.emplace_back(ins[i].second + 1);
    }
    cout << answer.size() << endl;
    for (int i = 0; i < answer.size(); i++) {
        cout << answer[i] << ' ';
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
