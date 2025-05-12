#include <cassert>
#include <cstdio>
#include <iostream>

using namespace ::std;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

const int N = 1001, M = 1001;

void solve() {
  int n, k;
  cin >> n >> k;
  for (int i = 0; i < n; i++) {
    if (i > 0) {
      cout << ' ';
    }
    if (k > 0) {
      cout << i * 2 + 2 << ' ' << i * 2 + 1;
    } else {
      cout << i * 2 + 1 << ' ' << i * 2 + 2;
    }
    k--;
  }
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
