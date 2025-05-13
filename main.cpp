#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <queue>

using namespace ::std;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

const int N = 1001, M = 1001;

void solve() {
  int n;
  cin >> n;
  pair<long long , int> arr[n];
  queue<pair<long long, int>> k_books;
  queue<pair<long long , int>> j_books;
  for (int i = 0; i < n; i++) {
    cin >> arr[i].first;
    arr[i].second = i;
  }
  sort(arr, arr + n);
  for (int i = 0; i < n; i++) {
    k_books.push(arr[i]);
  }
  reverse(arr, arr + n);
  for (int i = 0; i < n; i++) {
    j_books.push(arr[i]);
  }

  long long answer = 0;
  int locked[n];

  while (!k_books.empty() && !j_books.empty()) {

    if (k_books.front().second == j_books.front().second) {
      // TODO: create a heap for both to solve such cases
      if (locked[k_books.front().second] == 1) {
        pair<int, int> tmp = j_books.front();
        j_books.pop();
        j_books.push(tmp);
      } else {
        pair<int, int> tmp = k_books.front();
        k_books.pop();
        k_books.push(tmp);
      }
      if (k_books.front().second == j_books.front().second) {
        if (locked[k_books.front().second] == 1) {
          answer += k_books.front().first;
          locked[k_books.front().second] = 0;
          k_books.pop();
          if (!k_books.empty() && !locked[k_books.front().second]) {
            locked[k_books.front().second] = 1;
          }
        } else {
          answer += j_books.front().first;
          locked[j_books.front().second] = 0;
          j_books.pop();
          if (!j_books.empty() && !locked[j_books.front().second]) {
            locked[j_books.front().second] = 2;
          }
        }
      }
      continue;
    }

    if (k_books.front().first < j_books.front().first) {
      answer += k_books.front().first;
      j_books.front().first -= k_books.front().first;
      locked[k_books.front().second] = 0;
      k_books.pop();
      if (!k_books.empty() && !locked[k_books.front().second]) {
        locked[k_books.front().second] = 1;
      }
    } else if (k_books.front().first > j_books.front().first) {
      answer += j_books.front().first;
      k_books.front().first -= j_books.front().first;
      locked[j_books.front().second] = 0;
      j_books.pop();
      if (!j_books.empty() && !locked[j_books.front().second]) {
        locked[j_books.front().second] = 2;
      }
    } else {
      answer += j_books.front().first;
      j_books.pop();
      k_books.pop();
    }
  }

  while (!k_books.empty()) {
    answer += k_books.front().first;
    k_books.pop();
  }
  while (!j_books.empty()) {
    answer += j_books.front().first;
    j_books.pop();
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
