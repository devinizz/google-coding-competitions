#include "../../../../../include/prime_sieve.hpp"
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
using namespace std;

int pow(int n, int k, int mod) {
  if (k == 0)
    return 1;
  if (k % 2 == 0)
    return pow(1ll * n * n % mod, k / 2, mod);
  return 1ll * pow(n, k - 1, mod) * n % mod;
}

void sol() {
  static PrimeSieve pl(1e6);

  int D, K; cin >> D >> K;
  vector<long long> S(K); for(auto &s : S) cin >> s;

  if (K == 1) {
    cout << "I don't know.";
    return;
  } else if (K == 2 && S[0] != S[1]) {
    cout << "I don't know.";
    return;
  } else if (S[0] == S[1]) {
    cout << S[0];
    return;
  }

  set<int> ans;
  int from = *max_element(S.begin(), S.end());
  int to = pow(10, D);
  for (int p : pl) {
    if (p <= from) continue;
    if (p >= to) break;
    int A = (S[2] - S[1]) * pow(S[1] - S[0], p - 2, p) % p;
    int B = (S[1] - A * S[0]) % p;
    bool valid = true;
    for (int j = 3; j < K; j++) {
      if ((S[j] - S[j - 1] * A - B) % p != 0) {
        valid = false;
        break;
      }
    }
    if (valid)
      ans.insert(((S.back() * A + B) % p + p) % p);
  }

  if (ans.size() == 1)
    cout << *ans.begin();
  else
    cout << "I don't know.";
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
