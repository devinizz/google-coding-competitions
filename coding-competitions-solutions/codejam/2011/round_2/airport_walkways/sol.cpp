#include <iostream>
#include <map>
#include <cstdio>
using namespace std;

void sol() {
  int X, S, R, t, N; cin >> X >> S >> R >> t >> N;
  R -= S;
  map<int, int> m;
  int total_X = 0;
  for (int i = 0; i < N; i++) {
    int B, E, w; cin >> B >> E >> w;
    total_X += E - B;
    m[S + w] += E - B;
  }
  if (total_X < X)
    m[S] += X - total_X;
  double ans = 0;
  double total_t = 0;
  for (auto& it : m) {
    double use_t = min((double)it.second / (it.first + R), t - total_t);
    total_t += use_t;
    ans += (it.second - use_t * R) / it.first;
  }
  printf("%.6f\n", ans);
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
