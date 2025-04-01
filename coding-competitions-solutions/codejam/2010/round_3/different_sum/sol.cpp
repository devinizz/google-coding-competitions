#include <iostream>
#include <functional>
#include <map>
using namespace std;

void sol() {
  const int SIZE = 70;
  const int MOD = 1e9 + 7;

  long long N; int B; cin >> N >> B;
  int count[SIZE + 1][SIZE * SIZE] = {}; count[0][0] = 1;
  for (int i = 1; i < B; i++)
    for (int j = i; j > 0; j--)
      for (int k = 0; k < B * B; k++)
        count[j][k + i] = (count[j][k + i] + count[j - 1][k]) % MOD;

  int prod[SIZE + 1][SIZE];
  for (int i = 0; i <= B; i++) {
    prod[i][0] = 1;
    for (int j = 0; j < i; j++)
      prod[i][j + 1] = 1ll * prod[i][j] * (i - j) % MOD;
  }

  map<pair<long long, int>, int> memo;
  function<int(long long, int)> calc;
  calc = [&](long long n, int c) {
    if (n == 0) return (int)(c == 0);
    auto it = memo.find({n, c});
    if (it != memo.end()) return it->second;
    int ret = 0;
    for (auto i = n % B; i <= min(n, 1ll * B * B / 2); i += B) {
      for (int j = 0; j <= c; j++) {
        ret += 1ll * calc((n - i) / B, j) * count[c][i] % MOD * prod[c][j] % MOD;
        ret %= MOD;
        ret += 1ll * calc((n - i) / B, j) * count[c - 1][i] % MOD * j % MOD * prod[c - 1][j - 1] % MOD;
        ret %= MOD;
      }
    }
    memo[{n, c}] = ret;
    return ret;
  };
  int ans = 0;
  for (int i = 1; i <= B; i++)
    ans = (ans + calc(N, i)) % MOD;
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
