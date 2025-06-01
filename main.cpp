#include "util.h"
#include <cassert>
#include <cstdio>
#include <string>
#include <vector>

using namespace ::std;

int dx[4] = {0, 0, 1, -1}; // Up, Down, Right, Left
int dy[4] = {-1, 1, 0, 0}; // Up, Down, Right, Left

const int N = 1e4 + 1, M = 48, mod = 1e9 + 7;
#define in(i, j) i >= 0 && i < j
#define not_in(i, j) !(in(i, j))
int n, m;
string grid[N];
int dp[N][N];

#define interval pair<int, int>

class RangeModule {
  vector<interval> intervals;

public:
  void addRange(int left, int right) {
    vector<interval> result;
    interval tmp = {0, 0};
    int n = intervals.size();
    int i = 0;
    while (i < n) {
      interval current = intervals[i];
      if (current.second < left) {
        result.push_back(current);
      } else if (current.first > right) {
        tmp = {left, right};
        break;
      } else {
        left = min(left, current.first);
        right = max(right, current.second);
      }
      i++;
    }
    if (i == n) {
      result.push_back({left, right});
    } else {
      result.push_back(tmp);
    }
    while (i < n) {
      interval current = intervals[i];
      result.push_back(current);
      i++;
    }
    intervals = result;
  }
  bool queryRange(int left, int right) {
    int l = 0, r = intervals.size() - 1;
    while (l <= r) {
      int mid = l + (r - l) / 2;
      interval current = intervals[mid];
      if (current.first >= right) {
        r = mid - 1;
      } else if (current.second <= left) {
        l = mid + 1;
      } else {
        return current.first <= left && current.second >= right;
      }
    }
    return false;
  }
  void removeRange(int left, int right) {
    vector<interval> result;
    int n = intervals.size();
    int i = 0;
    while (i < n) {
      interval current = intervals[i];
      if (current.second <= left) {
        result.push_back(current);
      } else if (current.first >= right) {
        result.push_back(current);
      } else {
        if (current.first < left) {
          result.push_back({current.first, left});
        }
        if (intervals[i].second > right) {
          result.push_back({right, current.second});
        }
      }
      i++;
    }
    intervals = result;
  }
};

void solve() {}

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
