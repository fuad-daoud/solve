// lookuped up the tutorial, turned out I did not understand the problem
#include <cassert>
#include <iostream>
#include <set>
#include <vector>
using namespace ::std;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

void solve() {
  int n;
  cin >> n;
  vector<vector<int>> answer;
  for (int i = 0, j = 0; i < n; i = j) {
    set<int> seen;
    int x = -1;
    cin >> x;
    while (j < n && !seen.count(x)) {
      seen.insert(x);
      j++;
      if(j == n) {
        break;
      }
      cin >> x;
    }
    if (j == n) {
      break;
    }
    answer.push_back({i + 1, j + 1});
    j++;
  }
  if(answer.empty()) {
    cout << -1 << endl;
    return;
  }
  answer.back().back() = n;

  cout << answer.size() << endl;
  for(int i = 0; i < answer.size(); i++) {
    cout << answer[i][0] << ' ' << answer[i][1] << endl;
  }
}

int main() {
  // #ifdef ONLINE_JUDGE
  // assert(freopen("input2.txt", "rt", stdin));
  // freopen("output.txt", "w", stdout);
  // #endif
  int cases = 1;
  /*cin >> cases;*/
  while (cases--) {
    solve();
  }
  return 0;
}
