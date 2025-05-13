// lookedup the solution from usaco, need to rememeber when to use binary search
#include <algorithm>
#include <cassert>
#include <climits>
#include <cstdio>
#include <iostream>

using namespace ::std;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

const int N = 1001, M = 1001;

void solve() {
  int n;
  long long t;
  cin >> n >> t;
  int arr[n];
  int mn = INT_MAX;
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
    mn = min(mn, arr[i]);
  }

  long long left = 0;
  long long right = mn * t;
  long long res = 0;
  while (left <= right) {
    long long mid = (left + right) / 2;
    long long sum = 0;
    for (int i = 0; i < n; i++) {
      sum += (mid / arr[i]);
      if (sum >= t) {
        break;
      }
    }
    if (sum >= t) {
      res = mid;
      right = mid - 1;
    } else {
      left = mid + 1;
    }
  }
  cout << res << endl;
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
