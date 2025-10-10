#include <algorithm>
#include <vector>
#include <cassert>
#include <cstdio>
#include <cstring>
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
    int n;
    cin >> n;
    vector<int> next(1e6 + 1, -1), prev(1e6 + 1, -1);
    vector<int> numbers;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        next[a] = b;
        prev[b] = a;
        numbers.push_back(a);
    }
    vector<int> answer1;
    for (int x = next[0]; x > 0; x = next[x]) {
        answer1.push_back(x);
    }

    int start = 0;
    for (const int number : numbers) {
        if (prev[number] == -1) {
            start = number;
            break;
        }
    }
    vector<int> answer2;
    for (int x = start; x > 0; x = next[x]) {
        answer2.push_back(x);
    }
    vector<int> answer;
    for (int i = 0; i < n/2; i++) {
        answer.push_back(answer2[i]);
        answer.push_back(answer1[i]);
    }
    if (n % 2 == 1) {
        answer.push_back(answer2[n/2]);
    }
    for (const int number : answer) {
        cout << number << ' ';
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
