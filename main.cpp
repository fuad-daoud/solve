// looked up the solution from geeksforgeeks, I need to learn when to use heaps
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>

using namespace ::std;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

const int N = 1001, M = 1001;

struct customer {
  int id;
  bool status; // 0 means leaving, 1 means coming
  int room;
  int prev;
};

void solve() {
  int n;
  cin >> n;
  pair<int, int> ranges[n];
  for (int i = 0; i < n; i++) {
    cin >> ranges[i].first >> ranges[i].second;
  }

  vector<vector<int>> vec(n, vector<int>(3));
  for (int i = 0; i < n; i++) {
    vec[i][0] = ranges[i].first;
    vec[i][1] = ranges[i].second;
    vec[i][2] = i;
  }

  sort(vec.begin(), vec.end());

  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      occupied_rooms;

  int room_count = 0;

  vector<int> answer(n);

  for (int i = 0; i < n; i++) {
    int arrivalTime = vec[i][0];
    int departureTime = vec[i][1];
    int index = vec[i][2];

    if (occupied_rooms.empty() || occupied_rooms.top().first >= arrivalTime) {
      room_count += 1;
      occupied_rooms.push({departureTime, room_count});
      answer[index] = room_count;
    } else {
      int vacantRoom = occupied_rooms.top().second;
      occupied_rooms.pop();
      occupied_rooms.push({departureTime, vacantRoom});
      answer[index] = vacantRoom;
    }
  }

  cout << room_count << "\n";
  for (int i = 0; i < answer.size(); i++)
    cout << answer[i] << " ";
  cout << endl;
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
