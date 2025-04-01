#include <iostream>
#include <numeric>
using namespace std;

void sol() {
  const int MOD = 100003;
  const int SIZE = 501;
  auto cnk = [](int n, int k) {
    static int memo[SIZE][SIZE];
    if (!memo[0][0]) {
      memo[0][0] = memo[1][0] = memo[1][1] = 1;
      for (int i = 2; i < SIZE; i++) {
        memo[i][0] = 1;
        for (int j = 1; j <= i; j++)
          memo[i][j] = (memo[i - 1][j - 1] + memo[i - 1][j]) % MOD;
      }
    }
    return memo[n][k];
  };
  static int dp[SIZE][SIZE];
  if (!dp[2][1]) {
    for (int i = 2; i < SIZE; i++) {
      dp[i][1] = 1;
      for (int j = 2; j < i; j++)
        for (int k = 1; k < j; k++)
          dp[i][j] += (1ll * dp[j][k] * cnk(i - j - 1, j - k - 1)) % MOD;
    }
  }
  int n; cin >> n;
  cout << accumulate(dp[n], dp[n] + n, 0, [](int a, int b) {
      return (a + b) % MOD; });
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
