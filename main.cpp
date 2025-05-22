#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace ::std;

int dx[4] = {0, 0, 1, -1}; // Up, Down, Right, Left
int dy[4] = {-1, 1, 0, 0}; // Up, Down, Right, Left

const int N = 1000, M = 48, mod = 1e9 + 7;
#define in(i, j) i >= 0 && i < j
#define not_in(i, j) !(in(i, j))
int n, m;
string grid[N];
int dp[N][N];

void solve() {
  cin >> n >> m;
  // cout << m << endl;
  char s[n];
  scanf("%s", s);
  string answer;
  for (int i = 0; i < n; i++) {
    if (!m) {
      answer.push_back(s[i]);
      continue;
    }
    if (s[i] - 'a' > 'z' - s[i] && s[i] - 'a' <= m) {
      answer.push_back('a');
      m -= s[i] - 'a';
      continue;
    }
    if ('z' - s[i] > s[i] - 'a' && 'z' - s[i] <= m) {
      answer.push_back('z');
      m -= 'z' - s[i];
      continue;
    }
    if (s[i] + m < 'z') {
      answer.push_back(s[i] + m);
      m = 0;
      continue;
    }
    if (s[i] - m > 'a') {
      answer.push_back(s[i] - m);
      m = 0;
      continue;
    }
  }
  if (m) {
    cout << -1 << endl;
    return;
; }
  cout << answer << endl;
  // int test = 0;
  //
  // for (int i = 0; i < n; i++) {
  //   test += abs(s[i] - answer[i]);
  // }
  // cout << test << endl;
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
