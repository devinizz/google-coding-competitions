#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
using namespace std;

void sol() {
  int N; long long L, H; cin >> N >> L >> H;
  vector<long long> freqs(N);
  for (auto& freq : freqs)
    cin >> freq;
  sort(freqs.begin(), freqs.end());

  vector<long long> prefix_lcm(N + 1, H + 1);
  prefix_lcm[0] = 1;
  for (int i = 0; i < N; i++) {
    auto g = gcd(prefix_lcm[i], freqs[i]);
    if (prefix_lcm[i] / g > (H + freqs[i] - 1) / freqs[i])
      break;
    else
      prefix_lcm[i + 1] = prefix_lcm[i] / g * freqs[i];
  }

  vector<long long> suffix_gcd(N + 1, 0);
  for (int i = N - 1; i >= 0; i--)
    suffix_gcd[i] = std::gcd(freqs[i], suffix_gcd[i + 1]);

  long long ans = (L + prefix_lcm[N] - 1) / prefix_lcm[N] * prefix_lcm[N];
  for (int i = 0; i < N; i++) {
    auto M = prefix_lcm[i];
    if (M >= ans)
      break;

    auto G = suffix_gcd[i];
    if (G % M != 0 || G < L)
      continue;

    G /= M;
    for (int j = 1; j <= min(H / M, (long long)sqrt(G)); j++) {
      if (G % j != 0)
        continue;
      if (j * M >= L) {
        ans = j * M;
        break;
      }
      if (G / j * M >= L)
        ans = min(ans, G / j * M);
    }
  }
  if (ans <= H)
    cout << ans;
  else
    cout << "NO";
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
