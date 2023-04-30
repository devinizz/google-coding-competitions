#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void sol() {
  int P, K, L; cin >> P >> K >> L;
  vector<int> freq(L); for (int &f : freq) cin >> f;
  sort(freq.begin(), freq.end(), greater<int>());

  long long ans = 0;
  for (int i = 0; i < L; i++)
    ans += freq[i] * (static_cast<int>(i / K) + 1);

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
