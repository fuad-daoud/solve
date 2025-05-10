#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>

using namespace ::std;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

const int N = 1001, M = 1001;

void solve() {
  int n, q;
  scanf("%d %d", &n, &q);
  int l = int(log(n));
  pair<int, int> arr[n];
  for (int i = 0; i < n; i++) {
    scanf("%d", &arr[i].first);
    arr[i].second = 1;
  }
  for (int i = n - 2; i >= 0; i--) {
    if (arr[i].first == arr[i + 1].first) {
      arr[i].second = arr[i + 1].second + 1;
    }
  }

  while (q--) {
    int l, r, x;
    scanf("%d %d %d", &l, &r, &x);
    l--, r--;
    if (arr[l].first == x) {
      l += arr[l].second;
    }

    if (l > r) {
      printf("-1\n");
      continue;
    }
    printf("%d\n", l + 1);
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
