#include <iostream>
using namespace std;

void sol() {
  int N; cin >> N;
  int ans = 0;
  for (int i = 1; i <= N; i++) {
    int n; cin >> n;
    ans += n != i;
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
