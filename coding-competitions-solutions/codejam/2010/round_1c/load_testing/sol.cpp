#include <iostream>
#include <cmath>
using namespace std;

void sol() {
  int L, P, C; cin >> L >> P >> C;
  int ans = 0;
  double ratio = 1e0 * P / L;
  while (ratio > C) {
    ans++;
    ratio = sqrt(ratio);
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
