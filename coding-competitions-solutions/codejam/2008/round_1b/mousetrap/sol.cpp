#include <iostream>
#include <vector>
using namespace std;

void sol() {
  int K; cin >> K;
  int n; cin >> n;
  vector<int> d(n); for (int &i : d) cin >> i;
  vector<int> ans(n);
  for (int i = 1, pos = 0; i <= K; i++) {
    pos = (pos + i - 1) % (K - i + 1);
    for (int j = 0; j < n; j++) {
      if (ans[j] == 0) {
        if (d[j] == pos + 1)
          ans[j] = i;
        else if (d[j] > pos + 1)
          d[j]--;
      }
    }
  }
  for (int i = 0; i < n; i++)
    cout << ans[i] << (i < n - 1 ? " " : "");
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
