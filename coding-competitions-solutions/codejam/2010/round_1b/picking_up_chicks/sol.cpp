#include <iostream>
#include <vector>
using namespace std;

void sol() {
  int N, K, B, T; cin >> N >> K >> B >> T;
  vector<int> X(N); for (int &x : X) cin >> x;
  vector<int> V(N); for (int &v : V) cin >> v;
  int ans = 0;
  int k = 0;
  for (int i = N - 1, count = 0; i >= 0; i--) {
    if (k == K) break;
    if ((B - X[i]) > T * V[i]) {
      count++;
    } else {
      ans += count;
      k++;
    }
  }
  if (k < K)
    cout << "IMPOSSIBLE";
  else
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
