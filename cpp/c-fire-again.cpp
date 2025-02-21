#include <cstdio>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace ::std;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

void solve() {
  int n, m;
  cin >> n >> m;
  int k;
  cin >> k;

  queue<pair<int, int>> q;
  vector<vector<bool>> vis(n, vector<bool>(m, false));

  for(int i = 0; i < k; i++) {
    int x, y;
    cin >> x >> y;
    x--;y--;
    vis[x][y] = true;
    q.push(make_pair(x, y));
  }
  int x = -1;
  int y = -1;

  while(!q.empty()) {
    x = q.front().first;
    y = q.front().second;
    q.pop();

    for(int i = 0; i < 4; i++) {
      int nx = x + dx[i];
      int ny = y + dy[i];
      if(nx < 0 || ny < 0 || nx == n || ny == m || vis[nx][ny]) {
	continue;
      }
      vis[nx][ny] = true;
      q.push(make_pair(nx, ny));
    }
  }
  cout << x + 1 << ' ' << y + 1<< endl;

}

int main() {
#ifdef ONLINE_JUDGE
  freopen("output.txt", "w", stdout);
  freopen("input.txt", "r", stdin);
#endif
  int cases = 1;
  /*cin >> cases;*/
  while (cases--) {
    solve();
  }
  return 0;
}
