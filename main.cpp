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

const int N = 2e5 + 1, M = 48, mod = 1e9 + 7;
#define in(i, j) i >= 0 && i < j
#define not_in(i, j) !(in(i, j))
int n, m;
// string grid[N];
// int dp[N][N];
char chars[] = {'a', 'b', 'c'};

void solve() {
    string n;
    cin >> n;
    int answer1 = 1;
    switch (n[0]) {
        case '0': answer1++;
            break;
        case '1': answer1 += 6;
            break;
        case '2': answer1++;
            break;
        case '3': answer1 += 2;
            break;
        case '4': answer1 += 2;
            break;
        case '5': answer1 += 3;
            break;
        case '6': answer1++;
            break;
        case '7': answer1 += 4;
            break;
        case '8': break;
        case '9': answer1++;
            break;
    }

    int answer2 = 1;
    switch (n[1]) {
        case '0': answer2++;
            break;
        case '1': answer2 += 6;
            break;
        case '2': answer2++;
            break;
        case '3': answer2 += 2;
            break;
        case '4': answer2 += 2;
            break;
        case '5': answer2 += 3;
            break;
        case '6': answer2++;
            break;
        case '7': answer2 += 4;
            break;
        case '8': break;
        case '9': answer2++;
            break;
    }

    cout << answer1 * answer2 << endl;
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
