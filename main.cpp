#include <algorithm>
#include <vector>
#include <cassert>
#include <cmath>
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

const int N = 2e5 + 1, M = 48, mod = 1e9 + 7;
#define in(i, j) i >= 0 && i < j
#define not_in(i, j) !(in(i, j))
int n, m;
// string grid[N];
// int dp[N][N];
char chars[] = {'a', 'b', 'c'};

void solve() {
    string s;
    cin >> s;
    int counter = 0;

    for (const char i: s) {
        switch (i) {
            case '(': counter++;
                break;
            case ')': counter--;
                break;
            case '#': counter--;
            default: ;
        }
        if (counter < 0) {
            cout << -1 << endl;
            return;
        }
    }
    counter = 0;
    vector<int> answer;
    for (const char i: s) {
        switch (i) {
            case '(': counter++;
                break;
            case ')': counter--;
                break;
            case '#': counter--;
                answer.emplace_back(1);
                break;
            default: ;
        }
    }
    answer.back() += counter;
    counter = 0;
    int index = 0;

    for (const char i: s) {
        switch (i) {
            case '(': counter++;
                break;
            case ')': counter--;
                break;
            case '#': counter -= answer[index++];
            default: ;
        }
        if (counter < 0) {
            cout << -1 << endl;
            return;
        }
    }
    for (const int i: answer) {
        cout << i << endl;
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
