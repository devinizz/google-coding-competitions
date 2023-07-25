#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void sol() {
  const int MAX_DAY = 10000;
  int N, T; cin >> N >> T;
  vector<vector<int>> tournament(T);
  for (auto &days : tournament) {
    int m; cin >> m; days.resize(m);
    days[0] = 1;
    for (int i = 1; i < m; i++)
      cin >> days[i];
  }

  long long ans_N = 0, ans = 0;
  vector<int> count(T);
  for (int d = 1; d <= min(N, MAX_DAY); d++) {
    for (int t = 0; t < T; t++)
      if (binary_search(tournament[t].begin(), tournament[t].end(), d))
        count[t]++;
    for (int i = 0; i < T; i++)
      for (int j = i; j < T; j++)
        if (i == j)
          ans_N += count[i];
        else
          ans += 2 * count[i] * count[j];
  }
  for (int i = 0; i < T; i++)
    for (int j = i; j < T; j++)
      if (i == j)
        ans_N += 1ll * count[i] * max(0, N - MAX_DAY);
      else
        ans += 2ll * count[i] * count[j] * max(0, N - MAX_DAY);

  ans_N += ans / N; ans %= N;
  long long K = ans_N / N;
  long long A = ans_N % N * N + ans, B = 1ll * N * N;
  long long gcd = __gcd(A, B);
  cout << K << '+' << A / gcd << '/' << B / gcd;
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
