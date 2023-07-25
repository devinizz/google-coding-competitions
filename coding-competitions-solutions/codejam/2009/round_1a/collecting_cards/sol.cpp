#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void sol() {
  int C, N; cin >> C >> N;
  vector<double> dp(C + 1); dp[0] = 1;
  auto cnk = [](int n, int k) {
    if (k > n) return 0.;
    double d = 1;
    for (int i = 1; i <= k; i++) {
      d *= n - k + i;
      d /= i;
    }
    return d;
  };
  double ans = 0;
  for (double p = 1;;) {
    vector<double> dp2(C + 1);
    for (int i = 0; i < C; i++)
      for (int j = 0; j <= min(N, C - i); j++)
        dp2[i + j] += dp[i] * cnk(i, N - j) * cnk(C - i, j) / cnk(C, N);

    ans += p;
    p -= dp2[C];
    if (p < 1e-10)
      break;
    dp = move(dp2);
  }
  printf("%.7f", ans);
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
