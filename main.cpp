
#include <iostream>
using namespace ::std;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

void solve() {
  int a, b;
  cin >> a >> b;
  int answer = 0;
  while (a <= b) {
    int tmp = a;
    int mod = 10;
    int div = 1;

    while (true) {
      if (tmp / div == 0) {
        break;
      }
      int current = (tmp % mod) / div;
      mod *= 10;
      div *= 10;

      switch (current) {
      case 0:
      case 6:
      case 9:
        answer += 6;
        break;
      case 1:
        answer += 2;
        break;
      case 2:
      case 3:
      case 5:
        answer += 5;
        break;
      case 4:
        answer += 4;
        break;
      case 7:
        answer += 3;
        break;
      case 8:
        answer += 7;
        break;
      default:
        exit(123);
      }
    }
    a++;

  }
  cout << answer << endl;
}

int main() {
  // #ifdef ONLINE_JUDGE
  // freopen("output.txt", "w", stdout);
  // freopen("input.txt", "r", stdin);
  // #endif
  int cases = 1;
  /*cin >> cases;*/
  while (cases--) {
    solve();
  }
  return 0;
}
