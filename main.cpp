#include <cassert>
#include <cstdio>
#include <iostream>

using namespace ::std;

int dx[4] = {0, 0, 1, -1}; // Up, Down, Right, Left
int dy[4] = {-1, 1, 0, 0}; // Up, Down, Right, Left

const int N = 1000, M = 48;
#define in(i, j) i >= 0 && i < j
#define not_in(i, j) !(in(i, j))
int n;
string grid[N];

int go(int row = 0, int column = 0) {
  if (grid[row][column] == '*') {
    return 0;
  }
  if (row == n - 1 && column == n - 1) {
    return 1;
  }
  int result = 0;

  if (in(row + 1, n) && in(column, n)) {
    result += go(row + 1, column);
  }

  if (in(row, n) && in(column + 1, n)) {
    result += go(row, column + 1);
  }
  return result;
}

void solve() {
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> grid[i];
  }
  cout << go() << endl;;
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
