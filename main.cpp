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

// const int N = 1e4 + 1, M = 48, mod = 1e9 + 7;
#define in(i, j) i >= 0 && i < j
#define not_in(i, j) !(in(i, j))
int n, m;
// string grid[N];
// int dp[N][N];
char chars[] = {'a', 'b', 'c'};

struct state {
    string place;
    int cards;
    int player;
};

void solve() {
    int n;
    cin >> n;
    vector<long long> first_player, second_player;
    long long first_sum = 0, second_sum = 0;
    long long last = 0;

    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        if (x > 0) {
            first_player.emplace_back(x);
            first_sum += x;
        } else {
            second_player.emplace_back(x * -1);
            second_sum += x * -1;
        }
        last = x;
    }
    if (first_sum > second_sum) {
        cout << "first" << endl;
        return;
    }
    if (second_sum > first_sum) {
        cout << "second" << endl;
        return;
    }
    // if (first_player.size() > second_player.size()) {
    //     cout << "first" << endl;
    //     return;
    // }
    // if (second_player.size() > first_player.size()) {
    //     cout << "second" << endl;
    //     return;
    // }
    for (int i = 0; i < min(first_player.size(), second_player.size()); i++) {
        if (first_player[i] > second_player[i]) {
            cout << "first" << endl;
            return;
        }
        if (second_player[i] > first_player[i]) {
            cout << "second" << endl;
            return;
        }
    }
    if (last > 0) {
        cout << "first" << endl;
        return;
    }
    cout << "second" << endl;
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
