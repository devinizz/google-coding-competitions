#include <iostream>
#include <cmath>
#include "../../../../../include/prime_sieve.hpp"
using namespace std;

void sol() {
  static PrimeSieve primes(1000000);
  long long N; cin >> N;
  int ans = 1;
  for (auto p : primes) {
    if (p * p > N)
      break;
    int n = log(N) / log(p);
    if (pow(p, n + 1) <= N) // double check
      n++;
    ans += n - 1;
  }
  cout << (N == 1 ? 0 : ans);
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
