#include <algorithm>
#include <bitset>
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
#include <unordered_map>

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

void solve() {
    int n;
    cin >> n;
    int a;
    cin >> a;
    deque<int> arr_a;
    for (int i = 0; i < a; i++) {
        int x;
        cin >> x;
        arr_a.push_front(x);
    }
    int b;
    cin >> b;
    deque<int> arr_b;
    for (int i = 0; i < b; i++) {
        int x;
        cin >> x;
        arr_b.push_front(x);
    }
    vector<deque<int> > state_a, state_b;
    state_a.emplace_back(arr_a);
    state_b.emplace_back(arr_b);
    int rounds = 0;
    while (!arr_a.empty() && !arr_b.empty()) {
        rounds++;
        if (arr_b.back() > arr_a.back()) {
            int smaller_card = arr_a.back();
            arr_a.pop_back();
            arr_b.push_front(smaller_card);
            int bigger_card = arr_b.back();
            arr_b.pop_back();
            arr_b.push_front(bigger_card);
        } else {
            int smaller_card = arr_b.back();
            arr_b.pop_back();
            arr_a.push_front(smaller_card);
            int bigger_card = arr_a.back();
            arr_a.pop_back();
            arr_a.push_front(bigger_card);
        }


        for (int i = 0; i < state_a.size(); i++) {
            bool same = arr_a.size() == state_a[i].size() && arr_b.size() == state_b[i].size();
            if (!same) {
                continue;
            }

            for (auto it = arr_a.begin(), it_c = state_a[i].begin(); it != arr_a.end() && it_c != state_a[i].end();
                 ++it, ++it_c) {
                if (*it != *it_c) {
                    same = false;
                    break;
                }
            }

            for (auto it = arr_b.begin(), it_c = state_b[i].begin(); it != arr_b.end() && it_c != state_b[i].end();
                 ++it, ++it_c) {
                if (*it != *it_c) {
                    same = false;
                    break;
                }
            }
            if (same) {
                cout << -1 << endl;
                return;
            }
        }
        state_a.emplace_back(arr_a);
        state_b.emplace_back(arr_b);
    }
    cout << rounds << ' ' << (arr_a.empty() ? 2 : 1) << endl;
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
