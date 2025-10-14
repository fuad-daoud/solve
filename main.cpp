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
    string home, away;
    int n;
    cin >> home >> away;
    cin >> n;
    state timeline[91] = {};
    map<char, int[100]> trace = {};
    for (int i = 0; i < n; i++) {
        int time, player;
        char place, card;
        cin >> time >> place >> player >> card;
        timeline[time] = {
            home,
            card == 'r' ? 2 : 1 + timeline[trace[place][player]].cards,
            player,
        };
        trace[place][player] = time;
        if (place == 'a') {
            timeline[time].place = away;
        }
    }
    map<string, set<int>> seen;
    for (int i = 0; i < 91; i++) {
        if (const auto [place, cards, player] = timeline[i]; cards >= 2) {
            if (seen[place].count(player) == 1) {
                continue;
            }
            seen[place].insert(player);
            cout << place << ' ' << player << ' ' << i << endl;
        }
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
