#include <algorithm>
#include <cassert>
#include <cstdint>
#include <vector>
#include <iostream>

using namespace ::std;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

void solve() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> data(n, vector<int>(m));
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      cin >> data[i][j];
    }
  }
  for(int i = 0; i < n; i++) {
    sort(data[i].begin(), data[i].end());
  }
  int answer = INT32_MIN;

  for(int i = 0; i < n; i++) {
    answer = max(answer, data[i].front());
  }
  cout << answer << endl;
}

int main() {
  // #ifdef ONLINE_JUDGE
  // assert(freopen("input2.txt", "rt", stdin));
  // freopen("output.txt", "w", stdout);
  // #endif
  int cases = 1;
  /*cin >> cases;*/
  while (cases--) {
    solve();
  }
  return 0;
}
