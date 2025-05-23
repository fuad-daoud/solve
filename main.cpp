#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>

using namespace ::std;

int dx[4] = {0, 0, 1, -1}; // Up, Down, Right, Left
int dy[4] = {-1, 1, 0, 0}; // Up, Down, Right, Left

const int N = 1000, M = 48, mod = 1e9 + 7;
#define in(i, j) i >= 0 && i < j
#define not_in(i, j) !(in(i, j))
int n, m;
string grid[N];
int dp[N][N];

bool compare(string a, string b) { return a + b < b + a; }

void solve() {
  cin >> n;
  string s[n];
  for (int i = 0; i < n; i++) {
    cin >> s[i];
  }
  sort(s, s + n, compare);

  for (int i = 0; i < n; i++) {
    cout << s[i];
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
