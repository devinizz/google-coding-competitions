#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <cstring>
using namespace std;

void sol() {
  int N, M; cin >> N >> M;
  vector<string> calendar(N + 2);
  calendar[0] = calendar[N + 1] = string(M + 2, '.');
  for (int i = 1; i <= N; i++) {
    cin >> calendar[i];
    calendar[i] = '.' + calendar[i] + '.';
  }

  for (int i = 0; i < N + 2; i++)
    for (int j = i % 2; j < M + 2; j += 2)
      if (calendar[i][j] == '#')
        calendar[i][j] = '.';
      else if (calendar[i][j] == '.')
        calendar[i][j] = '#';

  int dr[4] = {0, -1, 1, 0};
  int dc[4] = {-1, 0, 0, 1};
  int ans = (N + 1) * M + (M + 1) * N;
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= M; j++) {
      if (calendar[i][j] == '#') {
        for (int d = 0; d < 4; d++)
          if (calendar[i + dr[d]][j + dc[d]] == '.')
            ans -= 1;
      } else if (calendar[i][j] == '.') {
        for (int d = 0; d < 4; d++)
          if (calendar[i + dr[d]][j + dc[d]] == '#')
            if (i + dr[d] == 0 || i + dr[d] == N + 1 ||
                j + dc[d] == 0 || j + dc[d] == M + 1)
              ans -= 1;
      }
    }
  }

  vector<vector<int>> edge(N + 2, vector<int>(M + 2));
  bool visited[52][52];
  function<bool(int, int)> dfs;
  dfs = [&](int i, int j) {
    visited[i][j] = true;
    for (int d = 0; d < 4; d++) {
      if (edge[i][j] & (1 << d)) continue;
      if (calendar[i + dr[d]][j + dc[d]] == '.') {
        edge[i][j] ^= 1 << d;
        return true;
      } else if (calendar[i + dr[d]][j + dc[d]] == '?') {
        if (!visited[i + dr[d]][j + dc[d]] && dfs(i + dr[d], j + dc[d])) {
          if (edge[i + dr[d]][j + dc[d]] & (1 << (3 - d)))
            edge[i + dr[d]][j + dc[d]] ^= 1 << (3 - d);
          else
            edge[i][j] ^= 1 << d;
          return true;
        }
      }
    }
    return false;
  };
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= M; j++) {
      if (calendar[i][j] == '?') {
        for (int d = 0; d < 4; d++) {
          if (calendar[i + dr[d]][j + dc[d]] == '#') {
            memset(visited, 0, sizeof(visited));
            ans -= dfs(i, j);
          }
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
