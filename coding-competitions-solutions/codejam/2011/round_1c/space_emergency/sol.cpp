#include <iostream>
#include <map>
#include <vector>
using namespace std;

void sol() {
  int L; long long t; int N, C; cin >> L >> t >> N >> C;
  t /= 2;
  vector<int> dist(C); for (int &d : dist) cin >> d;
  map<int, int> booster;
  long long ans = 0;
  for (int i = 0; i < N; i++) {
    auto d = dist[i % C];
    ans += d * 2;
    if (t >= d) {
      t -= d;
    } else {
      booster[d - t]++;
      t = 0;
    }
  }
  for (auto it = booster.rbegin(); it != booster.rend(); it++) {
    ans -= 1ll * min(L, it->second) * it->first;
    L -= min(L, it->second);
  }
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
