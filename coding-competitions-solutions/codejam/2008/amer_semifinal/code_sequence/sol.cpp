#include <iostream>
#include <vector>
using namespace std;

void sol() {
  const int MOD = 10007;
  int N; cin >> N;
  vector<int> S(N);
  for (int &s : S)
    cin >> s;

  for (int i = 1, r = 0, sum = 0;; i <<= 1) {
    vector<bool> v(2, true);
    for (int j = 0; j < 2; j++) {
      int k = r + j * i;
      if (k + i - 1 >= 2 * i)
        k = 0;
      if (k + i >= N)
        continue;
      int d = S[k + i] - S[k];
      for (int k = r + j * i; k + i < N; k += i * 2)
        if ((S[k + i] - S[k] - d) % MOD != 0)
          v[j] = false;
    }
    if (v[0] && v[1]) {
      cout << "UNKNOWN";
      return;
    }
    r += i * (v[0] ? 0 : 1);
    if ((N - 1 - r) % (2 * i) == i - 1) {
      cout << (S.back() - sum + S[r + i] - S[r] + MOD) % MOD;
      return;
    }
    sum = (sum + S[r + i] - S[r]) % MOD;
  }
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
