#include <algorithm>
#include <vector>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
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


void solve() {
    long long n, r, avg;
    cin >> n >> r >> avg;
    long long goal_sum = n * avg;
    pair<long long, long long> exams[n];
    long long current_sum = 0;
    for (int i = 0; i < n; i++) {
        long long a, b;
        cin >> a >> b;
        current_sum += a;
        exams[i] = {b, a};
    }


    sort(exams, exams + n);
    long long answer = 0;
    for (int i = 0; i < n; i++) {
        if (current_sum >= goal_sum) {
            break;
        }
        long long grades = min(goal_sum - current_sum, r - exams[i].second);
        current_sum += grades;
        answer += grades * exams[i].first;
    }
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
