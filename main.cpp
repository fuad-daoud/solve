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

const int N = 2e5 + 1, M = 48, mod = 1e9 + 7;
#define in(i, j) i >= 0 && i < j
#define not_in(i, j) !(in(i, j))
int n, m;
// string grid[N];
// int dp[N][N];
char chars[] = {'a', 'b', 'c'};

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    deque<char> ds;
    string answer = s;
    for (char c: s) {
        ds.emplace_back(c);
    }
    for (int x = 0; x < 10; x++) {
        for (char &c : ds) {
            if (c == '9') {
                c = '0';
                continue;
            }
            c++;
        }

        for (int i = 0; i < n; i++) {
            char tmp = ds.front();
            ds.pop_front();
            ds.emplace_back(tmp);

            int index = 0;
            for (const char c: ds) {
                if (c < answer[index]) {
                    answer = "";
                    for (const char cc: ds) {
                        answer.push_back(cc);
                    }
                    break;
                }
                if (c > answer[index]) {
                    break;
                }
                index++;
            }
        }
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
