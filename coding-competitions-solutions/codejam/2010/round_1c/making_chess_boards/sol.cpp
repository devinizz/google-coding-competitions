#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
using namespace std;

void sol() {
  int M, N; cin >> M >> N;

  vector<vector<bool>> board(M);
  for (int i = 0; i < M; i++) {
    string s; cin >> s;
    for (char c : s) {
      c -= c >= 'A' ? 'A' - 10 : '0';
      for (int mask = 8; mask > 0; mask >>= 1)
        board[i].push_back(c & mask);
    }
  }

  using P = pair<int, pair<int, int>>;
  priority_queue<P, vector<P>, greater<P>> pq;

  vector<vector<int>> prio(M, vector<int>(N));
  auto calc = [&](int i, int j) {
    int ret = 1;
    if (i != 0 && j != 0 &&
        board[i][j] != board[i - 1][j] &&
        board[i][j] != board[i][j - 1] &&
        board[i][j] == board[i - 1][j - 1])
      ret += min(prio[i - 1][j - 1], min(prio[i - 1][j], prio[i][j - 1]));
    return ret;
  };

  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      prio[i][j] = calc(i, j);
      pq.emplace(-prio[i][j], pair<int, int>(i , j));
    }
  }

  map<int, int> ans;
  while (!pq.empty()) {
    P cur = move(pq.top()); pq.pop();
    int p = -cur.first;
    int m = cur.second.first, n = cur.second.second;
    if (prio[m][n] != p) {
      if (prio[m][n] != 0)
        pq.emplace(-prio[m][n], pair<int, int>(m , n));
      continue;
    }
    ans[p]++;
    for (int i = m - p + 1; i < min(m + p, M); i++) {
      for (int j = n - p + 1; j < min(n + p, N); j++) {
        if ((i <= m && j <= n) || prio[i][j] == 0)
          prio[i][j] = 0;
        else
          prio[i][j] = calc(i, j);
      }
    }
  }

  cout << ans.size() << endl;
  for (auto it = ans.rbegin(); it != ans.rend(); it++)
    cout << it->first << ' ' << it->second << endl;
}

int main() {
  int T; cin >> T;
  for (int case_num = 1; case_num <= T; case_num++) {
    cout << "Case #" << case_num << ": ";

    sol();
  }
  return 0;
}
