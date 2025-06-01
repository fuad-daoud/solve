#include <algorithm>
#include <vector>
#ifndef ONLINE_JUDGE
#include "util.h"
#endif
#include <cassert>
#include <cstdio>
#include <iostream>
#include <stdio.h>

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

int gcd(int a, int b) {
  if (a == 0) {
    return b;
  }
  return gcd(b % a, a);
}

void solve() {
  cin >> n;
  int arr[n];
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }
  vector<pair<int, int>> answer;
  for (int i = 0; i < n - 1; i++) {
    int mx = max(arr[i], arr[i + 1]);
    int x = gcd(arr[i], arr[i + 1]);
    if (x > 1) {
      if (arr[i] == 1) {
        answer.push_back({i, 999983});
      } else {
        answer.push_back({i, 1});
      }
    }
  }
  cout << answer.size() << endl;
  for (int i = 0, j = 0; i < n; i++) {
    cout << arr[i] << ' ';
    if (j < answer.size() && answer[j].first == i) {
      cout << answer[j].second << ' ';
      j++;
    }
  }
  cout << endl;
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
