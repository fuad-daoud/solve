#include <cassert>
#include <cstdio>
#include <iostream>
#include <unordered_map>

using namespace ::std;

int dx[4] = {0, 0, 1, -1}; // Up, Down, Right, Left
int dy[4] = {-1, 1, 0, 0}; // Up, Down, Right, Left

const int N = 7, M = 48;
#define in(i, j) i >= 0 && i < j
#define not_in(i, j) !(in(i, j))

string s;
int dir[M];
bool vis[N][N];
int steps = 0, paths = 0;

void go(int column = 0, int row = 0) {
  // top and bottom walls
  if ((column >= 1 && column <= 5 && !vis[row][column - 1] &&
       !vis[row][column + 1]) &&
      ((row == 0 && vis[row + 1][column]) ||
       (row == N - 1 && vis[row - 1][column]))) {
    return;
  }
  // right and left walls
  if ((row >= 1 && row <= 5 && !vis[row - 1][column] &&
       !vis[row + 1][column]) &&
      ((column == 0 && vis[row][column + 1]) ||
       (column == N - 1 && vis[row][column - 1]))) {
    return;
  }
  if (column >= 1 && column <= 5 && row >= 1 && row <= 5) {
    if (!vis[row - 1][column] && !vis[row + 1][column] &&
        vis[row][column - 1] && vis[row][column + 1]) {
      return;
    }
    if (!vis[row][column - 1] && !vis[row][column + 1] &&
        vis[row - 1][column] && vis[row + 1][column]) {
      return;
    }
  }
  if (row == N - 1 && column == 0) {
    if (steps == 48) {
      paths++;
    }
    return;
  }
  if (dir[steps] != -1) {
    vis[row][column] = true;
    int current = dir[steps];
    steps++;
    int new_col = column + dx[current];
    int new_row = row + dy[current];

    // Inline the boundary checking
    if (in(new_row, N) && in(new_col, N) && !vis[new_row][new_col]) {
      go(new_col, new_row);
    }

    steps--;
    vis[row][column] = false;
    return;
  }

  for (int i = 0; i < 4; i++) {
    int new_col = column + dx[i];
    int new_row = row + dy[i];

    if (in(new_row, N) && in(new_col, N) && !vis[new_row][new_col]) {
      vis[row][column] = true;
      steps++;
      go(new_col, new_row);
      steps--;
      vis[row][column] = false;
    }
  }
}

void solve() {
  cin >> s;
  const char dir_chars[] = "UDRL";
  unordered_map<char, int> dir_map = {
      {'U', 0}, {'D', 1}, {'R', 2}, {'L', 3}, {'?', -1}};
  for (int i = 0; i < M; i++) {
    dir[i] = dir_map[s[i]];
  }
  go();
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
