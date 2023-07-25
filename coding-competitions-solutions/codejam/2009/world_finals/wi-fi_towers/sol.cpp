#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <functional>
using namespace std;

void sol() {
  struct Tower {
    int x, y, r, s;
    bool inrange(const Tower &t) {
      static auto square = [](int x) { return x * x; };
      return r * r >= square(x - t.x) + square(y - t.y);
    }
  };
  int n; cin >> n;
  vector<Tower> towers(n);
  for (Tower &tower : towers)
    cin >> tower.x >> tower.y >> tower.r >> tower.s;

  vector<vector<int>> to(n);
  vector<map<int, int>> from(n);
  vector<bool> visited(n);
  for (int i = 0; i < n; i++) {
    if (towers[i].s <= 0) continue;
    fill(visited.begin(), visited.end(), false);
    vector<int> v; v.push_back(i); visited[i] = true;
    for (unsigned j = 0; j < v.size(); j++) {
      for (int k = 0; k < n; k++) {
        if (visited[k]) continue;
        if (towers[v[j]].inrange(towers[k])) {
          visited[k] = true;
          if (towers[k].s < 0)
            to[i].push_back(k);
          v.push_back(k);
        }
      }
    }
  }

  function<int(int, int)> dfs;
  dfs = [&](int i, int flow) {
    visited[i] = true;
    for (int j : to[i]) {
      if (visited[j]) continue;
      visited[j] = true;
      if (towers[j].s < 0) {
        int f = min(-towers[j].s, flow);
        towers[j].s += f;
        from[j][i] += f;
        return f;
      }
      for (auto &p : from[j]) {
        if (visited[p.first]) continue;
        int f = dfs(p.first, min(p.second, flow));
        if (f) {
          if (f == p.second)
            from[j].erase(p.first);
          else
            from[j][p.first] -= f;
          from[j][i] += f;
          return f;
        }
      }
    }
    return 0;
  };

  int ans = 0;
  for (int i = 0; i < n; i++) {
    if (towers[i].s <= 0) continue;
    while (towers[i].s > 0) {
      fill(visited.begin(), visited.end(), false);
      int flow = dfs(i, towers[i].s);
      if (flow == 0) break;
      towers[i].s -= flow;
    }
    ans += towers[i].s;
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
