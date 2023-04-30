#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <cstring>
using namespace std;

void sol() {
  const int MAX_SIZE = 80;
  bool visited[MAX_SIZE + 2][MAX_SIZE + 2] = {0,};
  int ans = 0;

  int M, N; cin >> M >> N;
  vector<string> seats(M + 2);
  seats[0] = seats[M + 1] = string(N + 2, 'x');
  for (int i = 1; i <= M; i++) {
    cin >> seats[i];
    for (auto &c : seats[i])
      ans += c == '.';
    seats[i] = 'x' + seats[i] + 'x';
  }
  int dr[6] = {-1, 0, 1, -1, 0, 1};
  int dc[6] = {-1, -1, -1, 1, 1, 1};
  function<bool(int, int)> dfs;
  dfs = [&](int i, int j) {
    for (int d = 0; d < 6; d++) {
      int r = i + dr[d], c = j + dc[d];
      if (visited[r][c] || seats[r][c] == 'x')
        continue;
      visited[r][c] = true;
      int b = seats[r][c];
      if (b == '.' || dfs(r - dr[b], c - dc[b])) {
        seats[r][c] = d;
        return true;
      }
    }
    return false;
  };
  for (int i = 1; i <= M; i++) {
    for (int j = 1; j <= N; j += 2) {
      memset(visited, 0, sizeof(visited));
      if (seats[i][j] == '.')
        if (dfs(i, j))
          ans--;
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
