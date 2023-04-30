#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <cstring>
using namespace std;

struct state {
  int r, c, pr, pc;
  state(int r, int c, int pr, int pc) : r(r), c(c), pr(pr), pc(pc) {}
  state next(int d) {
    switch (d) {
      default:
      case 0: return {r - 1, c, pr, pc};
      case 1: return {r + 1, c, pr, pc};
      case 2: return {r, c - 1, pr, pc};
      case 3: return {r, c + 1, pr, pc};
    }
  }
};
#define ADDR1(state) state.r][state.c
#define ADDR2(state) state.r][state.c][state.pr][state.pc

void sol() {
  int R, C; cin >> R >> C;
  unsigned prio[R + 2][C + 2][R + 2][C + 2];
  memset(prio, -1, sizeof(prio));
  deque<state> q;

  vector<string> grid(R + 2);
  grid[0] = grid[R + 1] = string(C + 2, '#');
  for (int i = 1; i <= R; i++) {
    cin >> grid[i];
    grid[i] = '#' + grid[i] + '#';
    auto j = grid[i].find('O');
    if (j != string::npos) {
      state start(i, j, 0, 0);
      prio[ADDR2(start)] = 0;
      q.push_back(start);
    }
  }

  int ans = -1;
  while (!q.empty()) {
    state cur = q.front();
    unsigned pri = prio[ADDR2(cur)];
    if (grid[ADDR1(cur)] == 'X') {
      ans = pri;
      break;
    }
    q.pop_front();

    for (int d = 0; d < 4; d++) {
      state nxt = cur;
      while (grid[ADDR1(nxt.next(d))] != '#')
        nxt = nxt.next(d);

      nxt = {cur.r, cur.c, nxt.r, nxt.c};
      if (prio[ADDR2(nxt)] > pri) {
        prio[ADDR2(nxt)] = pri;
        q.push_front(nxt);
      }
    }

    for (int d = 0; d < 4; d++) {
      state nxt = cur.next(d);
      if (grid[ADDR1(nxt)] == '#') {
        if (cur.pr > 0 && cur.pc > 0)
          nxt = {cur.pr, cur.pc, 0, 0};
        else
          continue;
      }
      if (prio[ADDR2(nxt)] > pri + 1) {
        prio[ADDR2(nxt)] = pri + 1;
        q.push_back(nxt);
      }
    }
  }

  if (ans == -1)
    cout << "THE CAKE IS A LIE";
  else
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
