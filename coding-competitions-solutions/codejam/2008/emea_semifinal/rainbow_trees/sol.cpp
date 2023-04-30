#include <iostream>
#include <vector>
#include <functional>
using namespace std;

void sol() {
  const int MOD = 1e9 + 9;
  int n, k; cin >> n >> k;
  vector<vector<int>> edges(n + 1);
  vector<int> count(n + 1, -1); count[1] = 0;
  for (int i = 1; i < n; i++) {
    int x, y; cin >> x >> y;
    edges[x].push_back(y);
    edges[y].push_back(x);
  }
  function<int(int)> calc;
  calc = [&](int r) {
    int ret = 1, child = 0, prod = k - count[r];
    for (int t : edges[r]) {
      if (count[t] == -1) {
        ret = 1ll * ret * prod-- % MOD;
        child++;
      }
    }
    for (int t : edges[r]) {
      if (count[t] == -1) {
        count[t] = child + (count[r] > 0);
        ret = 1ll * ret * calc(t) % MOD;
      }
    }
    return ret;
  };
  cout << calc(1);
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
