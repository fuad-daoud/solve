#include <cassert>
#include <cstdio>
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
  string s;
  cin >> s;
  long long answer = 0;
  for (int i = s.size() - 1; i >= 1; i--) {
    string str = "";
    str += s[i - 1];
    str += s[i];
    int num;

    sscanf(str.c_str(), "%d", &num);
    if (num % 4 == 0) {
      answer += i;
    }
  }

  for (int i = 0; i < s.size(); i++) {
    string str = "";
    str += s[i];
    int num;
    sscanf(str.c_str(), "%d", &num);

    if (num % 4 == 0) {
      answer++;
    }
  }
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
