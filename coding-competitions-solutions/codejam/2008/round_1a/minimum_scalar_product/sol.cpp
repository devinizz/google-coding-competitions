#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void sol() {
  int n; cin >> n;
  vector<int> v1(n); for (int &x : v1) cin >> x;
  vector<int> v2(n); for (int &x : v2) cin >> x;
  sort(v1.begin(), v1.end());
  sort(v2.begin(), v2.end(), greater<int>());

  long long ans = 0;
  for (int i = 0; i < n; i++)
    ans += 1ll * v1[i] * v2[i];

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
