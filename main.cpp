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

// const int N = 3 * 1e4 + 7, M = 250, mod = 1e9 + 7;
#define in(i, j) i >= 0 && i < j
#define not_in(i, j) !(in(i, j))
// int n, l, m;
// string grid[N];
// int dp[N][N];


vector<string> splitString(const string &str, char delimiter) {
    vector<string> tokens;
    string token;
    stringstream ss(str);

    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void printStack(std::stack<string> s) {
    if (s.empty()) {
        return;
    }
    string x = s.top();
    s.pop();
    printStack(s);
    cout << x << "/";
}

void solve() {
    int n;
    cin >> n;
    stack<string> state;
    while (n--) {
        string x;
        cin >> x;
        if (x == "pwd") {
            cout << "/";
            printStack(state);
            cout << endl;
            continue;
        }
        if (x == "cd") {
            cin >> x;
            vector<string> tokens = splitString(x, '/');
            for (const string& token: tokens) {
                if (token.empty()) {
                    while (!state.empty()) {
                        state.pop();
                    }
                    continue;
                }
                if (token == "..") {
                    state.pop();
                } else {
                    state.push(token);
                }
            }
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
