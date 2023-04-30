#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

void sol() {
  struct Painter {
    int A, B, C;
    Painter(int A, int B, int C) : A(A), B(B), C(C) {}
    bool operator<(const Painter& p) const { return this->A < p.A; }
  };
  int N; cin >> N;
  map<string, int> colors;
  vector<Painter> painters;;
  for (int i = 0; i < N; i++) {
    string C; int A, B; cin >> C >> A >> B;
    if (colors.find(C) == colors.end())
      colors[C] = colors.size();
    painters.emplace_back(A, B, colors[C]);
  }
  sort(painters.begin(), painters.end());
  int ans = N + 1;
  for (int i = 0; i < colors.size(); i++) {
    for (int j = i; j < colors.size(); j++) {
      for (int k = j; k < colors.size(); k++) {
        int count = 1, p = 1, m = 0;
        for (auto &painter : painters) {
          int a = painter.A;
          int b = painter.B;
          int c = painter.C;
          if (c == i || c == j || c == k) {
            if (p < a) {
              p = m + 1;
              count++;
              if (p < a) break;
            }
            if (count >= ans) break;
            m = max(m, b);
            if (m == 10000) {
              ans = min(ans, count);
              break;
            }
          }
        }
      }
    }
  }
  if (ans > N)
    cout << "IMPOSSIBLE";
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
