#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace ::std;

int dx[4] = {0, 0, 1, -1}; // Up, Down, Right, Left
int dy[4] = {-1, 1, 0, 0}; // Up, Down, Right, Left

const int N = 1000, M = 48, mod = 1e9 + 7;
#define in(i, j) i >= 0 && i < j
#define not_in(i, j) !(in(i, j))
int n;
string grid[N];
int dp[N][N];

int go(int row = 0, int column = 0) {
  if (dp[row][column] != -1) {
    return dp[row][column];
  }
  if (grid[row][column] == '*') {
    return 0;
  }
  if (row == n - 1 && column == n - 1) {
    return 1;
  }
  int result = 0;

  if (in(row + 1, n) && in(column, n)) {
    result = (result + go(row + 1, column)) % mod;
  }
  if (in(row, n) && in(column + 1, n)) {
    result = (result + go(row, column + 1))% mod;
  }
  dp[row][column] = result % mod;
  return result;
}

void solve() {
  cin >> n;
  memset(dp, -1, sizeof(dp));
  for (int i = 0; i < n; i++) {
    cin >> grid[i];
  }
  dp[0][0] = go();
  cout << dp[0][0] << endl;
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
