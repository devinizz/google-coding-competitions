#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void sol() {
  int N, M; cin >> N >> M;
  vector<int> U(M), V(M);
  for (int& x : U) cin >> x;
  for (int& x : V) cin >> x;
  vector<vector<int>> rooms(1);
  for (int i = 1; i <= N; i++)
    rooms[0].push_back(i);
  int C = N;
  for (int i = 0; i < M; i++) {
    for (auto &room : rooms) {
      auto start = lower_bound(room.begin(), room.end(), U[i]);
      auto end = upper_bound(room.begin(), room.end(), V[i]);
      if (start != room.end() && *start == U[i] && *(end - 1) == V[i]) {
        vector<int> new_room(start, end);
        room.erase(start + 1, end - 1);
        C = min({C, (int)room.size(), (int)new_room.size()});
        rooms.push_back(std::move(new_room));
        break;
      }
    }
  }
  vector<int> color(N + 1);
  int colored = 0;
  while (colored < N) {
    for (auto &room : rooms) {
      vector<int> used;
      for (int v : room) {
        if (color[v])
          used.push_back(color[v]);
      }
      int nxt_color = 0;
      if (colored == 0 || used.size() == 2) {
        for (int i = 0; i < room.size(); i++) {
          if (color[room[i]])
            continue;
          int last = color[room[i == 0 ? room.size() - 1 : i - 1]];
          int next = color[room[(i + 1) % room.size()]];
          nxt_color = nxt_color % C + 1;
          while (find(used.begin(), used.end(), nxt_color) != used.end())
            nxt_color = nxt_color % C + 1;
          while (nxt_color == next || nxt_color == last)
            nxt_color = nxt_color % C + 1;
          color[room[i]] = nxt_color;
          colored++;
        }
      }
    }
  }

  cout << C << endl;
  for (int i = 1; i <= N; i++)
    cout << (i == 1 ? "" : " ") << color[i];
}

int main() {
  int T; cin >> T;
  for (int case_num = 1; case_num <= T; case_num++) {
    cout << "Case #" << case_num << ": ";

    sol();

    cout << '\n';
  }
  return 0;
}
