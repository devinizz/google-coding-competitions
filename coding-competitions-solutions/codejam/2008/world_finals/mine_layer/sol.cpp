#include <iostream>
#include <vector>
using namespace std;

void sol() {
  int R, C; cin >> R >> C;
  vector<vector<int>> clues(R, vector<int>(C));
  for (auto &v : clues)
    for (int &x : v)
      cin >> x;
  auto calc = [&](int r) {
    int s = 0;
    for (int c = C % 3 ? 0 : 1; c < C; c += 3)
      s += clues[r][c];
    return s;
  };
  int total = 0;
  for (int r = R % 3 ? 0 : 1; r < R; r += 3)
    total += calc(r);
  int h = (R - 1) / 2;
  int S = 0;
  if (h % 3 == 1) {
    for (int r = h - 1; r >= 0; r -= 3)
      S += calc(r);
    for (int r = h + 1; r < R; r += 3)
      S += calc(r);
    cout << S - total;
  } else {
    for (int r = h - 2; r >= 0; r -= 3)
      S += calc(r);
    for (int r = h + 2; r < R; r += 3)
      S += calc(r);
    cout << total - S;
  }
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
