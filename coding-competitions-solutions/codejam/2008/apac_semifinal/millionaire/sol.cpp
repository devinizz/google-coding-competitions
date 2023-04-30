#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

void sol() {
  int M; double P; int X; cin >> M >> P >> X;
  M = 1 << M; X = X / 1e6 * M;

  vector<double> dp(M + 1);
  dp[M] = 1;
  for (int i = M >> 1; i > 0; i >>= 1) {
    vector<double> nxt(dp);
    for (int j = i; j < M; j += i)
      for (int k = i; k <= min(j, M - j); k += i)
        nxt[j] = max(P * dp[j + k] + (1 - P) * dp[j - k], nxt[j]);
    dp = move(nxt);
  }
  printf("%.9lf", dp[X]);
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
