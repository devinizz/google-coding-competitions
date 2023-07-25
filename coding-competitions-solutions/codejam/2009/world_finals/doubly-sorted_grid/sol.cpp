#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>
using namespace std;

void sol() {
  const int MOD = 10007;
  const int MAX_SIZE = 10;

  int R, C; cin >> R >> C;
  vector<string> grid(R);
  for (string &s : grid)
    cin >> s;

  static int dp[1 << (2 * MAX_SIZE)][26][MAX_SIZE];
  memset(dp, 0, sizeof(dp));
  string P = string(R, '0') + string(C, '1');
  dp[stoi(P, nullptr, 2)][0][0] = 1;
  for (;;) {
    int p = stoi(P, nullptr, 2);
    for (int c = 0; c < 26; c++) {
      dp[p][c][0] += c > 0 ? dp[p][c - 1][C - 1] : 0;
      for (int mask = 1, i = -1, j = C; j > 0; mask <<= 1) {
        if (p & mask) {
          j--;
          if (i >= 0 && (p & (mask >> 1)) == 0)
            if (grid[i][j] == '.' || grid[i][j] == 'a' + c)
              dp[p][c][j] += dp[p - (mask >> 1)][c][j];
        } else {
          i++;
        }
      }
      for (int j = 0; j < C; j++) {
        dp[p][c][j] += j > 0 ? dp[p][c][j - 1] : 0;
        dp[p][c][j] %= MOD;
      }
    }
    if (!next_permutation(P.begin(), P.end()))
      break;
  }
  cout << dp[((1 << C) - 1) << R]['z' - 'a'][C - 1];
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
