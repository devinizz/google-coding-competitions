#include <iostream>
#include <vector>
#include <functional>
#include <set>
#include <cstdio>
using namespace std;

void sol() {
  const int MAX_P = 400;

  int P, W; cin >> P >> W;
  vector<int> edges[P];
  for (int i = 0; i < W; i++) {
    int x, y; scanf("%d,%d", &x, &y);
    edges[x].push_back(y);
    edges[y].push_back(x);
  }
  vector<int> dist(P, P);
  dist[1] = 0;
  {
    vector<int> bfs(1, 1);
    for (int i = 0; i < bfs.size(); i++) {
      auto cur = bfs[i];
      for (auto planet : edges[cur]) {
        if (dist[cur] + 1 < dist[planet]) {
          bfs.push_back(planet);
          dist[planet] = dist[cur] + 1;
        }
      }
    }
  }
  set<int> memo[MAX_P][MAX_P];
  function<int(int, int, set<int>)> calc = [&](int from, int to, set<int> threaten) {
    if (to == 1)
      return (int)threaten.size();
    threaten.insert(edges[to].begin(), edges[to].end());
    if (memo[from][to].size() >= threaten.size())
      return 0;
    memo[from][to] = threaten;
    int ret = threaten.size();
    for (auto p : edges[to])
      if (dist[p] < dist[to])
        ret = max(ret, calc(to, p, threaten));
    return ret;
  };
  cout << dist[0] - 1 << ' ' << calc(0, 0, {0}) - dist[0];
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
