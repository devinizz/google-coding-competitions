#include <iostream>
#include <vector>
#include <functional>
using namespace std;

void sol() {
  int n, k; cin >> n >> k;
  vector<vector<int>> prices(n, vector<int>(k));
  for (auto &v : prices)
    for (int &x : v)
      cin >> x;

  vector<vector<int>> edge(n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int p = 0;
      while(p < k && prices[i][p] < prices[j][p])
        p++;
      if (p == k)
        edge[i].push_back(j);
    }
  }
  vector<bool> visited(n);
  vector<int> prev(n, -1);
  function<bool(int)> dfs;
  dfs = [&](int i) {
    for (int j : edge[i]) {
      if (visited[j]) continue;
      visited[j] = true;
      if (prev[j] == -1 || dfs(prev[j])) {
        prev[j] = i;
        return true;
      }
    }
    return false;
  };
  int ans = n;
  for (int i = 0; i < n; i++) {
    fill(visited.begin(), visited.end(), false);
    ans -= dfs(i);
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
