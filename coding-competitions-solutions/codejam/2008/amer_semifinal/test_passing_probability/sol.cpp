#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

void sol() {
  int M, Q; cin >> M >> Q;
  vector<double> dp(1, 1);
  for (int i = 0; i < Q; i++) {
    vector<double> cur[4];
    for (int j = 0; j < 4; j++) {
      double prob; cin >> prob;
      for (double d : dp)
        cur[j].push_back(d * prob);
    }
    vector<double> m[2];
    merge(cur[0].begin(), cur[0].end(), cur[1].begin(), cur[1].end(),
          back_inserter(m[0]), greater<double>());
    merge(cur[2].begin(), cur[2].end(), cur[3].begin(), cur[3].end(),
          back_inserter(m[1]), greater<double>());
    dp.clear();
    merge(m[0].begin(), m[0].end(), m[1].begin(), m[1].end(),
          back_inserter(dp), greater<double>());
    dp.resize(min(static_cast<int>(dp.size()), M));
  }
  double ans = 0;
  for (int i = 0; i < min(static_cast<int>(dp.size()), M); i++)
    ans += dp[i];
  printf("%.9lf", ans);
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
