#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
using namespace std;

void sol() {
  int R, C; cin >> R >> C;
  vector<string> board(R + 2);
  board[0] = board[R + 1] = string(C + 2, '#');

  using State = vector<pair<int, int>>;
  State start, end;
  for (int i = 1; i <= R; i++) {
    cin >> board[i];
    board[i] = '#' + board[i] + '#';
    for (int j = 1; j <= C; j++) {
      if (board[i][j] == 'o') {
        start.emplace_back(i, j);
      } else if (board[i][j] == 'x') {
        end.emplace_back(i, j);
      } else if (board[i][j] == 'w') {
        start.emplace_back(i, j);
        end.emplace_back(i, j);
      }
    }
  }
  sort(start.begin(), start.end());
  sort(end.begin(), end.end());

  auto next = [&](const State &st) {
    static int dr[4] = {0, -1, 0, 1};
    static int dc[4] = {-1, 0, 1, 0};
    static auto safe = [&](const State &st) {
      State v; v.push_back(st[0]);
      for (unsigned i = 0; i < v.size(); i++) {
        for (int d = 0; d < 4; d++) {
          auto cur = make_pair(v[i].first + dr[d], v[i].second + dc[d]);
          if (find(st.begin(), st.end(), cur) != st.end() &&
              find(v.begin(), v.end(), cur) == v.end())
            v.push_back(cur);
        }
      }
      return v.size() == st.size();
    };

    vector<State> nxt;
    bool s = safe(st);
    for (unsigned i = 0; i < st.size(); i++) {
      for (int d = 0; d < 2; d++) {
        int r[2] = {st[i].first + dr[d], st[i].first + dr[d | 2]};
        int c[2] = {st[i].second + dc[d], st[i].second + dc[d | 2]};
        if (board[r[0]][c[0]] != '#' && board[r[1]][c[1]] != '#' &&
            find(st.begin(), st.end(), make_pair(r[0], c[0])) == st.end() &&
            find(st.begin(), st.end(), make_pair(r[1], c[1])) == st.end()) {
          for (int j = 0; j < 2; j++) {
            State cur(st);
            cur[i] = {r[j], c[j]};
            sort(cur.begin(), cur.end());
            if (s || safe(cur))
              nxt.push_back(cur);
          }
        }
      }
    }
    return nxt;
  };

  map<State, int> moves; moves[start] = 0;
  vector<State> v; v.push_back(start);
  for (unsigned i = 0; i < v.size(); i++) {
    if (v[i] == end) {
      cout << moves[end];
      return;
    }
    for (auto &state : next(v[i])) {
      if (moves.find(state) == moves.end()) {
        moves[state] = moves[v[i]] + 1;
        v.push_back(state);
      }
    }
  }
  cout << -1;
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
