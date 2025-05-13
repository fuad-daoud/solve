#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <numeric>

using namespace ::std;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

const int N = 1001, M = 1001;

void solve() {
  int n;
  cin >> n;
  long long arr[n];
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }
  sort(arr, arr + n);

  long long mx = arr[n - 1];

  long long sm = accumulate(arr, arr + n - 1, 0ll);
  if (mx <= sm) {
    cout << sm + mx << endl;
    return;
  }
  cout << mx * 2 << endl;
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
