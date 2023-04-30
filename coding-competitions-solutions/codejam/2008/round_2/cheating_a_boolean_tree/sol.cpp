#include <iostream>
#include <vector>
using namespace std;

void sol() {
  int M, V; cin >> M >> V;

  struct {
    vector<pair<int, int>> vp;
    void add(int G, int C) { vp.emplace_back(G, C); }
    int sol(int V, unsigned n = 0) {
      if (n >= (vp.size() - 1) / 2)
        return vp[n].first == V ? 0 : vp.size();
      int l = sol(V, n * 2 + 1), r = sol(V, n * 2 + 2);
      if (vp[n].first == V) {
        if (vp[n].second)
          return min(l + r, 1 + min(l, r));
        return l + r;
      }
      return min(l, r);
    }
  } bt;
  for (int i = 0; i < M; i++) {
    int G; cin >> G;
    int C;
    if (i < (M - 1) / 2)
      cin >> C;
    bt.add(G, C);
  }
  int ans = bt.sol(V);
  if (ans < M)
    cout << ans;
  else
    cout << "IMPOSSIBLE";
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
