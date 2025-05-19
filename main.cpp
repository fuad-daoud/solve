#include <cassert>
#include <cstdio>
#include <iostream>

using namespace ::std;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

const int N = 7, M = 48;
#define in(i, j) i >= 0 || i < j
#define not_in(i, j) !(in(i, j))

string s;
bool vis[N][N];
int steps = 0, paths = 0;

void go(int column = 0, int row = 0) {
  if ((row < 0 || row > N - 1) || (column < 0 || column > N - 1)) {
    return;
  }
  if (vis[row][column]) {
    return;
  }

  // top and bottom walls
  if ((column >= 1 && column <= 5 && !vis[row][column - 1] && !vis[row][column + 1]) && ((row == 0 && vis[row + 1][column]) || (row == N - 1 && vis[row - 1][column]))){
    return;
  }
  // right and left walls
  if ((row >= 1 && row <= 5 && !vis[row - 1][column] && !vis[row + 1][column]) && ((column == 0 && vis[row][column + 1]) || (column == N - 1 && vis[row][column - 1]))){
    return;
  }
  if (column >= 1 && column <= 5 && row >= 1 && row <= 5) {
    if (!vis[row - 1][column] && !vis[row + 1][column] && vis[row][column - 1] && vis[row][column + 1]){
      return;
    }
    if (!vis[row][column - 1] && !vis[row][column + 1] && vis[row - 1][column] && vis[row + 1][column]){
      return;
    }
  }
  if (row == N - 1 && column == 0) {
    if (steps == 48) {
      paths++;
    }
    return;
  }
  for (int i = 0; i < 4; i++) {
    vis[row][column] = true;
    steps++;
    go(column + dx[i], row + dy[i]);
    steps--;
    vis[row][column] = false;
  }
}

void solve() {
  cin >> s;
  go(0, 0);
  cout << paths << endl;
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
