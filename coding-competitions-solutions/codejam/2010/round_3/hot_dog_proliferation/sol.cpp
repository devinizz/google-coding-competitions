#include <iostream>
#include <vector>
#include <functional>
using namespace std;

void sol() {
  int C; cin >> C;
  long long ans = 0;
  vector<pair<int, int>> seg;
  auto sq = [](int x) { return 1ll * x * x; };
  auto add_seg = [&](int a, int b) {
    if (!seg.empty() && seg.back().second == a - 1)
      seg.back().second = b;
    else
      seg.emplace_back(a, b);
  };
  function<void(int)> add = [&](int p) {
    if (seg.back().second < p) {
      add_seg(p, p);
      return;
    } else if (seg.back().first <= p) {
      auto top = move(seg.back()); seg.pop_back();
      int hole = top.first + top.second - p;
        ans += sq(top.first - 1) + sq(top.second + 1);
        ans -= sq(hole) + sq(p);
        add_seg(top.first - 1, hole - 1);
        add_seg(hole + 1, top.second + 1);
    } else {
      auto top = move(seg.back()); seg.pop_back();
      add(p);
      add_seg(top.first, top.second);
    }
  };
  for (int i = 0; i < C; i++) {
    int P, V; cin >> P >> V;
    if (seg.empty()) {
      seg.emplace_back(P, P);
      V--;
    }
    for (int j = 0; j < V; j++)
      add(P);
  }
  cout << ans / 2;
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
