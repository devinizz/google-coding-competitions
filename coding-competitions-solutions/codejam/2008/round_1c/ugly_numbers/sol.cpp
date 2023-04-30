#include <iostream>
#include <string>
#include <vector>
using namespace std;

void sol() {
  const int MOD = 2 * 3 * 5 * 7;
  string s; cin >> s;
  vector<int> digits;
  for (char c : s)
    digits.push_back(c - '0');
  int D = digits.size();

  long long dp[D + 1][MOD] = {1,};
  for (int i = 0; i < D; i++) {
    for (int j = i, n = 0; j < D; j++) {
      n = (10 * n + digits[j]) % MOD;
      for (int k = 0; k < MOD; k++) {
        dp[j + 1][(k + n) % MOD] += dp[i][k];
        if (i != 0)
          dp[j + 1][(k - n + MOD) % MOD] += dp[i][k];
      }
    }
  }

  long long ans = 0;
  for (int i = 0; i < MOD; i++)
    if (i % 2 == 0 || i % 3 == 0 || i % 5 == 0 || i % 7 == 0)
      ans += dp[D][i];
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
