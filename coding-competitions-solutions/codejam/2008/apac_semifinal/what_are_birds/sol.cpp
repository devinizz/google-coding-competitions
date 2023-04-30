#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

void sol() {
  struct Bird {
    int bl, bh;
    Bird(int bl = 1e6, int bh = 1) : bl(bl), bh(bh) {}
    Bird add(int n) const { return {min(bl, n), max(bh, n)}; }
    bool is_bird(int n) const { return n >= bl && n <= bh; }
  } h, w;
  vector<pair<int, int>> vp;
  int N; cin >> N;
  for (int i = 0; i < N; i++) {
    int H, W; cin >> H >> W;
    string X; cin.ignore(); getline(cin, X);
    if (X == "BIRD") {
      h = h.add(H);
      w = w.add(W);
    } else {
      vp.emplace_back(H, W);
    }
  }
  int M; cin >> M;
  for (int i = 0; i < M; i++) {
    int H, W; cin >> H >> W;
    string s = "UNKNOWN";
    if (h.is_bird(H) && w.is_bird(W)) {
      s = "BIRD";
    } else {
      for (auto &p : vp) {
        if (h.add(H).is_bird(p.first) && w.add(W).is_bird(p.second)) {
          s = "NOT BIRD";
          break;
        }
      }
    }
    cout << s << endl;
  }
}

int main() {
  int T; cin >> T;
  for (int case_num = 1; case_num <= T; case_num++) {
    cout << "Case #" << case_num << ":" << endl;

    sol();
  }
  return 0;
}
