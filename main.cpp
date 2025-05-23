#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
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

void solve() {
  cin >> n;
  long long arr[n];
  for (long long i = 0; i < n; i++) {
    cin >> arr[i];
  }
  string s;
  cin >> s;
  long long answer = -1;
  long long prefix[n + 1];
  memset(prefix, 0, sizeof(prefix));

  for (long long i = 1; i < n + 1; i++) {
    if (s[i - 1] == 'B') {
      prefix[i] = prefix[i - 1] + arr[i - 1];
    } else {
      prefix[i] = prefix[i - 1];
    }
  }

  long long suffix[n + 1];
  memset(suffix, 0, sizeof(suffix));

  for (long long i = n - 1; i >= 0; i--) {
    if (s[i] == 'B') {
      suffix[i] = suffix[i + 1] + arr[i];
    } else {
      suffix[i] = suffix[i + 1];
    }
  }

  long long sum = 0;
  for (long long i = 0; i < n; i++) {
    if (s[i] == 'A') {
      sum += arr[i];
    }
    if (i == n - 1) {
      answer = max(answer, sum);
      continue;
    }
    answer = max(answer, sum + suffix[i + 1]);
  }
  sum = 0;
  for (long long i = n - 1; i >= 0; i--) {
    if (s[i] == 'A') {
      sum += arr[i];
    }
    answer = max(answer, sum + prefix[i]);
  }
  answer = max(answer, suffix[0]);
  cout << answer << endl;
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
