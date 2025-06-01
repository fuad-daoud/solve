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

void solve() {
  string s;
  cin >> s;
  int n = s.size();
  for (int i = 0; i < n - 2; i++) {
    if (s[i] == s[i + 1]) {
      for (auto c : chars) {
        if (s[i] != c && s[i + 2] != c) {
          s[i + 1] = c;
          break;
        }
      }
    }
  }
  if (s[n - 2] == s[n - 1]) {
    for (auto c : chars) {
      if (s[n - 2] != c) {
        s[n - 1] = c;
        break;
      }
    }
  }

  cout << s << endl;
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
