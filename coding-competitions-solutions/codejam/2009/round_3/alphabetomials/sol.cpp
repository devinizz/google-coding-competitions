#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

void sol() {
  const int MOD = 10009;
  string p; int K; cin >> p >> K;
  int n; cin >> n;
  vector<string> words(n);
  for (string &word : words)
    cin >> word;

  vector<int> ans(K);
  for (char &c : p)
    c = c == '+' ? ' ' : c;
  istringstream iss(p);
  while (iss >> p) {
    vector<int> base(1 << p.size());
    for (unsigned i = 0; i < base.size(); i++) {
      for (string &word : words) {
        int prod = 1;
        for (unsigned j = 0; j < p.size(); j++)
          if (i & 1 << j)
            prod *= count(word.begin(), word.end(), p[j]);
        base[i] = (base[i] + prod) % MOD;
      }
    }
    vector<int> dp(base.size()); dp[0] = 1;
    for (int i = 0; i < K; i++) {
      vector<int> cur(base.size());
      for (unsigned j = 0; j < base.size(); j++)
        for (unsigned k = 0; k < base.size(); k++)
          if ((j & k) == 0)
            cur[j ^ k] = (cur[j ^ k] + dp[j] * base[k]) % MOD;
      ans[i] = (ans[i] + cur.back()) % MOD;
      dp = move(cur);
    }
  }

  for (int i = 0; i < K; i++)
    cout << ans[i] << (i == K - 1 ? "" : " ");
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
