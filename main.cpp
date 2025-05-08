#include <cassert>
#include <iostream>
#include <set>

using namespace ::std;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

const int N = 1001, M = 1001;

bool vis[N][M];
pair<int, int> leader_map[N][M];
int leaders[N][M];
string grid[N];

int check(int y, int x, int n, int m, int leader_y, int leader_x) {
  if (y == -1 || y >= n) {
    return 0;
  }
  if (x == -1 || x >= m) {
    return 0;
  }
  if (vis[y][x]) {
    return 0;
  }
  if (grid[y][x] == '*') {
    return 0;
  }
  vis[y][x] = true;
  leader_map[y][x] = {leader_y, leader_x};
  int size = 1;

  for (int i = 0; i < 4; i++) {
    size += check(y + dy[i], x + dx[i], n, m, leader_y, leader_x);
  }
  return size;
}

void solve() {
  int n, m;
  cin >> n >> m;

  for (int i = 0; i < n; i++) {
    string x;
    cin >> x;
    grid[i] = x;
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (vis[i][j]) {
        continue;
      }
      leaders[i][j] = check(i, j, n, m, i, j);
    }
  }

  string answer[n];
  for (int i = 0; i < n; i++) {
    answer[i] = grid[i];
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (grid[i][j] == '.') {
        continue;
      }
      set<pair<int, int>> seen_leaders;
      int size = 1;
      for (int k = 0; k < 4; k++) {
        int y = i + dy[k], x = j + dx[k];
        if (y == -1 || y >= n) {
          continue;
        }
        if (x == -1 || x >= m) {
          continue;
        }
        if(grid[y][x] == '*') {
          continue;
        }
        pair<int, int> leader = leader_map[y][x];
        if (seen_leaders.count(leader)) {
          continue;
        }
        size += leaders[leader.first][leader.second];
        seen_leaders.insert(leader);
      }
      answer[i][j] = size % 10 + '0';
    }
  }

  for (int i = 0; i < n; i++) {
    cout << answer[i] << endl;
  }
}

int main() {
  // #ifdef ONLINE_JUDGE
  // assert(freopen("input.txt", "rt", stdin));
  // freopen("output.txt", "w", stdout);
  // #endif
  int cases = 1;
  /*cin >> cases;*/
  while (cases--) {
    solve();
  }
  return 0;
}
