#include <iostream>
#include <vector>
using namespace std;

void sol() {
  int N; cin >> N;
  vector<int> A(N), B(N);
  int ans = 0;
  for (int i = 0; i < N; i++) {
    cin >> A[i] >> B[i];
    for (int j = 0; j < i; j++)
      ans += (A[i] - A[j]) * (B[i] - B[j]) < 0;
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
