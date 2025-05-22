// lookedup the solution 
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
  int b, p;
  cin >> n >> b >> p;
  int t = n * p;
  int x = 0;
  while (n > 1) {
    int k = 1;
    while (k * 2 <= n) {
      k *= 2;
    }
    x += (k / 2) * (2 * b + 1);
    n -= k / 2;
  }
  cout << x << ' ' << t << endl;
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
