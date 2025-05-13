// I lookedup the tutorial
#include <cassert>
#include <cstdio>
#include <iostream>

using namespace ::std;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

const int N = 1001, M = 1001;

bool beats(int n, int j, int i) {
  if (j == 0) {
    return i == n - 1;
  }
  if (j == n - 1) {
    return i != 0;
  }
  return j > i;
}

void solve() {
  int n;
  cin >> n;
  string s;
  cin >> s;
  bool good = false;
  for (int i = 0; i < n; i++) {
    if (s[i] != 'A') {
      continue;
    }
    bool good_move = true;
    for (int j = 0; j < n; j++) {
      if (s[j] == 'B' && beats(n, j, i)) {
        good_move = false;
      }
    }
    if (good_move) {
      good = true;
    }
  }
  if (good) {
    cout << "Alice" << endl;
    return;
  }
  cout << "Bob" << endl;
}

int main() {
#ifndef ONLINE_JUDGE
  assert(freopen("input.txt", "rt", stdin));
// freopen("output.txt", "w", stdout);
#endif
  int cases = 1;
  cin >> cases;
  while (cases--) {
    solve();
  }
  return 0;
}
