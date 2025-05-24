#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

using namespace ::std;

int dx[4] = {0, 0, 1, -1}; // Up, Down, Right, Left
int dy[4] = {-1, 1, 0, 0}; // Up, Down, Right, Left

const int N = 1e4 + 1, M = 48, mod = 1e9 + 7;
#define in(i, j) i >= 0 && i < j
#define not_in(i, j) !(in(i, j))
int n, m;
string grid[N];
int dp[N][N];

vector<vector<int>> merge(vector<vector<int>> &intervals) {
  // int mx = -1;
  int n = intervals.size();
  int arr[N][2];
  memset(arr, 0, sizeof(arr));
  for (int i = 0; i < n; i++) {

    arr[intervals[i][0]][0]++;
    arr[intervals[i][1]][1]++;
    // mx = max(mx, max(intervals[i][1], intervals[i][0]));
  }

  // for (int i = 0; i < mx; i++) {
  //   cout << arr[i][0] << ' ';
  // }
  // cout << endl;
  // for (int i = 0; i < mx; i++) {
  //   cout << arr[i][1] << ' ';
  // }
  // cout << endl;

  vector<vector<int>> answer;

  int opened = 0, closed = 0;

  vector<int> current(2);

  for (int i = 0; i < N; i++) {
    if (arr[i][0] > 0) {
      if (!opened) {
        current[0] = i;
      }
      opened += arr[i][0];
    }
    if (arr[i][1] > 0) {
      closed += arr[i][1];
      if (closed == opened) {
        current[1] = i;
        answer.push_back(current);
        current = vector<int>(2);
        closed = 0;
        opened = 0;
      }
    }
  }
  return answer;
}

void solve() {
  cin >> n;
  vector<vector<int>> intervals(n, vector<int>(2));
  for (int i = 0; i < n; i++) {
    cin >> intervals[i][0] >> intervals[i][1];
  }
  vector<vector<int>> answer = merge(intervals);

  // for (int i = 0; i < answer.size(); i++) {
  //   cout << answer[i][0] << ' ' << answer[i][1] << endl;
  // }
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
