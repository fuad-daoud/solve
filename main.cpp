// I lookedup the tutorial
#include <cassert>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace ::std;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

const int N = 1001, M = 1001;

void solve() {
  int n;
  cin >> n;
  int arr[n];
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }

  vector<int> tails;
  for (int i = 0; i < n; i++) {
    int left = 0, right = tails.size();
    while (left < right) {
      int mid = (left + right) / 2;
      if (tails[mid] < arr[i]) {
        left = mid + 1;
      } else {
        right = mid;
      }
    }
    if(left == tails.size()) {
      tails.push_back(arr[i]);
    } else {
      tails[left] = arr[i];
    }
  }
  cout << tails.size() << endl;
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
