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
char chars[] = {'a', 'b', 'c'};

void solve() {
    int n;
    long long sum = 0;
    cin >> n;
    int arr[n];
    int largest = INT_MIN, second_largest = INT_MIN + 1;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        if (arr[i] > largest) {
            second_largest = largest;
            largest = arr[i];
        } else if (arr[i] == largest) {
            second_largest = largest;
        } else if (arr[i] > second_largest) {
            second_largest = arr[i];
        }
        sum += arr[i];
    }
    vector<int> answer;
    for (int i = 0; i < n; i++) {
        sum -= arr[i];
        int target = largest;
        if (arr[i] == largest) {
            target = second_largest;
        }
        sum -= target;
        if (sum == target) {
            answer.emplace_back(i + 1);
        }
        sum += target;
        sum += arr[i];
    }
    cout << answer.size() << endl;
    for (const int x: answer) {
        cout << x << ' ';
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
