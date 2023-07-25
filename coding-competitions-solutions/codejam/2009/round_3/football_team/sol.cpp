#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

void sol() {
  const int MAX_SIZE = 1000;
  int N; cin >> N;
  vector<pair<int, int>> players(N);
  for (auto &player : players)
    cin >> player.first >> player.second;
  sort(players.begin(), players.end());

  int ans = 1;
  bool g[MAX_SIZE][MAX_SIZE] = {0,};
  for (int i = 0; i < N; i++) {
    for (int y = players[i].second - 1; y <= players[i].second + 1; y++) {
      for (int j = i + 1; j < N; j++) {
        if (players[j].second == y) {
          g[i][j] = g[j][i] = true;
          ans = 2;
          break;
        }
      }
    }
  }

  vector<int> color(N);
  bool visited[MAX_SIZE][MAX_SIZE] = {0,};
  function<bool(int, int)> check;
  check = [&](int i, int j) {
    if (visited[i][j]) return true;
    visited[i][j] = visited[j][i] = true;
    int c = 3 - color[i] - color[j];
    for (int k = 0; k < N; k++) {
      if (g[i][k] && g[j][k]) {
        ans = 3;
        if (color[k] != -1 && color[k] != c)
          return false;
        color[k] = c;
        if (!check(i, k) || !check(j, k))
          return false;
      }
    }
    return true;
  };

  for (int i = 0; i < N; i++) {
    for (int j = i + 1; j < N; j++) {
      if (g[i][j]) {
        fill(color.begin(), color.end(), -1);
        color[i] = 0; color[j] = 1;
        if (!check(i, j)) {
          cout << 4;
          return;
        }
      }
    }
  }
  cout << ans;
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
