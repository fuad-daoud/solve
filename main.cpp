#include <algorithm>
#include <cassert>
#include <iostream>

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

  long long cm[n + 1];
  cm[n] = 0l;
  for(int i = n - 1; i >= 0; i--) {
    cm[i] = cm[i + 1] + arr[i];
  }
  long long mx[n];
  mx[0] = arr[0];
  for(int i = 1; i < n; i++) {
    mx[i] = max(mx[i - 1], arr[i]);
  }
  for (int i = 1; i <= n; i++) {
    int last_index = n - i;
    long long last = mx[last_index];
    last += cm[last_index + 1];
    cout << last << ' ';
  }
  cout << endl;
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
