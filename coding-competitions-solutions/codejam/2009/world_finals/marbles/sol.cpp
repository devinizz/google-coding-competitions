#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <functional>
using namespace std;

void sol() {
  const int INF = 1e9;
  int n; cin >> n;

  map<string, int> colors;
  vector<int> marbles;
  vector<vector<int>> where(n);
  for (int i = 0; i < 2 * n; i++) {
    string s; cin >> s;
    if (colors.find(s) == colors.end())
      colors[s] = colors.size();
    marbles.push_back(colors[s]);
    where[colors[s]].push_back(i);
  }

  auto cross = [&](int m1,int m2) {
    return
      where[m1][0] < where[m2][0] &&
      where[m2][0] < where[m1][1] &&
      where[m1][1] < where[m2][1] ||
      where[m2][0] < where[m1][0] &&
      where[m1][0] < where[m2][1] &&
      where[m2][1] < where[m1][1];
  };

  vector<int> y(n);
  vector<vector<int>> groups(2 * n);

  for (int i = 0; i < n; i++) {
    if (!y[i]) {
      vector<int> v; v.push_back(i); y[i] = 1;
      vector<int> &group = groups[where[i][0]];
      for (unsigned j = 0; j < v.size(); j++) {
        for (int m = 0; m < n; m++) {
          if (cross(m, v[j]) && y[m] != -y[v[j]]) {
            if (y[m] == y[v[j]]) {
              cout << -1;
              return;
            }
            y[m] = -y[v[j]];
            v.push_back(m);
          }
        }
        group.push_back(where[v[j]][0]);
        group.push_back(where[v[j]][1]);
      }
      sort(group.begin(), group.end());
    }
  }

  vector<vector<int>> memo(2 * n, vector<int>(n, -1));
  function<int(int, int, int)> calcH2;
  calcH2 = [&](int a, int b, int h1) {
    if (h1 < 0) return INF;
    if (a == b) return 0;
    int &res = memo[a][h1];
    if (res != -1) return res;
    vector<int> &group = groups[a];
    res = INF;
    for (int h = -1; h <= 1; h += 2) {
      int top = 0, bot = 0;
      int h2 = 0;
      for (unsigned i = 0; i < group.size() - 1; i++) {
        int &t = y[marbles[group[i]]] == h ? top : bot;
        t += where[marbles[group[i]]][0] == group[i] ? 1 : -1;
        h2 = max(h2, calcH2(group[i] + 1, group[i + 1], h1 - top) + bot);
      }
      h2 = max(h2, calcH2(group.back() + 1, b, h1));
      res = min(res, h2);
    }
    return res;
  };

  int res = INF;
  for (int h1 = 0; h1 < n; h1++)
    res = min(res, h1 + calcH2(0, 2 * n, h1));
  cout << res;
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
