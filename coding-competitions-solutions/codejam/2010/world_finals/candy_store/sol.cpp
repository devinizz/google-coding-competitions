#include <iostream>
using namespace std;

void sol() {
  int k; long long C; cin >> k >> C;
  int ans = 0;
  long long s = 0;
  for (long long i = 1; i <= C;) {
    int x = (k - s + i - 1) / i;
    ans += x;
    s += x * i;
    i += s / k;
    s %= k;
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
