#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
using namespace std;

void sol() {
  int k; cin >> k;
  string S; cin >> S;
  int weight[k][k]; memset(weight, 0, sizeof(weight));
  for (unsigned q = 0; q < S.size() / k; q++)
    for (int i = 0; i < k; i++)
      for (int j = 0; j < k; j++)
        weight[i][j] += (S[i + q * k] != S[j + q * k]);

  int dp[1 << k][k];
  int ans = S.size();
  for (int d = 0; d < k; d++) {
    for (int i = 1; i < 1 << k; i++) {
      if (i & (1 << d)) continue;
      for (int j = 0; j < k; j++) {
        if (i & (1 << j)) {
          if (i == 1 << j) {
            dp[i][j] = weight[j][d];
          } else {
            dp[i][j] = S.size();
            for (int n = 0; n < k; n++)
              if ((i ^ (1 << j)) & (1 << n))
                dp[i][j] = min(dp[i][j], dp[i ^ (1 << j)][n] + weight[j][n]);
          }
        }
      }
    }
    for (int i = 0; i < k; i++) {
      if (i == d) continue;
      int curr = dp[((1 << k) - 1) ^ (1 << d)][i];
      for (unsigned q = 1; q < S.size() / k; q++)
        curr += S[d - k + q * k] != S[i + q * k];
      ans = min(ans, curr);
    }
  }

  cout << ans + 1;
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
