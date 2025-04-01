#include <iostream>
#include <vector>
using namespace std;

void sol() {
  const int SIZE = 1e6 + 1;
  int A1, A2, B1, B2; cin >> A1 >> A2 >> B1 >> B2;
  vector<int> win(SIZE); win[1] = 2; win[2] = 4;
  int pos = 3;
  for (int i = 2; i < SIZE; i++) {
    while (pos < min(win[i], SIZE)) {
      win[pos] = pos + i;
      pos++;
    }
  }
  long long ans = 0;
  for (int i = A1; i <= A2; i++) {
    int b1 = max(B1, win[i]);
    ans += max(0, B2 - b1 + 1);
  }
  for (int i = B1; i <= B2; i++) {
    int a1 = max(A1, win[i]);
    ans += max(0, A2 - a1 + 1);
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
