#include <iostream>
using namespace std;

void sol() {
  int N, K; cin >> N >> K;
  int mask = (1 << N) - 1;
  cout << ((K & mask) == mask ? "ON" : "OFF");
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
