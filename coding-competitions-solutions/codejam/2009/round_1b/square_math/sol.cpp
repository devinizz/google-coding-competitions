#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <set>

using namespace std;

void sol() {
  int W, Q; cin >> W >> Q;

  vector<string> square(W);
  for (string &s : square)
    cin >> s;

  vector<int> queries(Q);
  for (int &query : queries)
    cin >> query;

  using State = tuple<int, int, int>;
  queue<State> q;
  map<State, string> path;
  for (int i = 0; i < W; i++) {
    for (int j = 0; j < W; j++) {
      if (square[i][j] >= '0') {
        State t(i, j, square[i][j] - '0');
        q.push(t);
        path[t] = square[i][j];
      }
    }
  }

  set<int> qs(queries.begin(), queries.end());
  map<int, string> ans;
  int dr[4] = {0, 0, -1, 1};
  int dc[4] = {-1, 1, 0, 0};
  unsigned bound = 1e9;
  while (!q.empty()) {
    State st = q.front(); q.pop();
    int r = get<0>(st), c = get<1>(st), v = get<2>(st);
    string s = path[st];
    if (s.size() > bound)
      break;
    if (qs.find(v) != qs.end()) {
      if (ans[v].empty() ||
        (s.size() == ans[v].size() && s.compare(ans[v]) < 0))
        ans[v] = s;
      if (ans.size() == qs.size())
        bound = s.size();
    }

    for (int d1 = 0; d1 < 4; d1++) {
      int r2 = r + dr[d1], c2 = c + dc[d1];
      if (r2 < 0 || r2 >= W || c2 < 0 || c2 >= W) continue;
      for (int d2 = 0; d2 < 4; d2++) {
        int r3 = r2 + dr[d2];
        int c3 = c2 + dc[d2];
        if (r3 < 0 || r3 >= W || c3 < 0 || c3 >= W) continue;
        string cur = s + square[r2][c2] + square[r3][c3];
        State nxt(r3, c3,
            v + (square[r3][c3] - '0') * (square[r2][c2] == '+' ? 1 : -1));
        string &old = path[nxt];
        if (old.empty()) {
          q.push(nxt);
          old = cur;
        } else if (cur.size() <= old.size() && cur.compare(old) < 0) {
          old = cur;
        }
      }
    }
  }
  for (int query : queries)
    cout << ans[query] << endl;
}

int main() {
  int T; cin >> T;
  for (int case_num = 1; case_num <= T; case_num++) {
    cout << "Case #" << case_num << ":\n";

    sol();
  }
  return 0;
}
