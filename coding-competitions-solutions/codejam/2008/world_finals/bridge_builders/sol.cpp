#include <iostream>
#include <vector>
#include <string>
using namespace std;

void sol() {
  int N, M; cin >> N >> M;
  vector<string> grid(N + 2);
  grid[0] = grid[N + 1] = string(M + 2, '.');
  for (int i = 1; i <= N; i++) {
    cin >> grid[i];
    grid[i] = '.' + grid[i] + '.';
  }

  auto bfs = [&](vector<pair<int, int>> &f) {
    static const int dr[4] = {0, 0, -1, 1};
    static const int dc[4] = {-1, 1, 0, 0};
    vector<vector<bool>> visited(N + 2, vector<bool>(M + 2));
    for (auto &p : f)
      visited[p.first][p.second] = true;
    vector<pair<int, int>> cur(f);
    for (int d = 1; !cur.empty(); d++) {
      vector<pair<int, int>> nxt;
      for (auto &p : cur) {
        for (int i = 0; i < 4; i++) {
          int r = p.first + dr[i], c = p.second + dc[i];
          if (!visited[r][c]) {
            visited[r][c] = true;
            if (grid[r][c] == '#')
              nxt.emplace_back(r, c);
            else if (grid[r][c] == 'T')
              return pair<pair<int, int>, int>({r, c}, d);
          }
        }
      }
      cur = move(nxt);
    }
    return pair<pair<int, int>, int>({0, 0}, 0);
  };
  int ans = 0;
  vector<pair<int, int>> forest; forest.emplace_back(1, 1);
  for (;;) {
    auto p = bfs(forest);
    int d = p.second;
    if (d == 0) break;
    ans += d * (d + 1) / 2;
    ans -= (d / 2) * (d / 2 + 1);
    if (d % 2 == 0) ans += d / 2;
    forest.push_back(p.first);
  }
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= M; j++) {
      if (grid[i][j] == '#') {
        vector<pair<int, int>> v; v.emplace_back(i, j);
        auto p = bfs(v);
        ans += p.second;
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
