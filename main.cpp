#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace ::std;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

void solve() {
  string a, b;
  cin >> a >> b;
  string tmp = "";
  int diff = abs(int(a.size() - b.size()));
  for (int i = 0; i < diff; i++) {
    tmp.append("0");
  }
  if (a.size() < b.size()) {
    a.insert(0, tmp);
  } else if (b.size() < a.size()) {
    b.insert(0, tmp);
  }
  int i = 0, j = 0;

  while (i < a.size() && j < b.size()) {
    if (a[i] > b[j]) {
      cout << ">" << endl;
      return;
    } else if (a[i] < b[j]) {
      cout << "<" << endl;
      return;
    }
    i++, j++;
  }
  if (i == a.size() && j == b.size()) {
    cout << "=" << endl;
    return;
  }
  if (i == a.size()) {
    cout << "<" << endl;
    return;
  }

  if (j == b.size()) {
    cout << "<" << endl;
    return;
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
