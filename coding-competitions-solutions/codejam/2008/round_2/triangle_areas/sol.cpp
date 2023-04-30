#include <iostream>
using namespace std;

void sol() {
  int N, M, A; cin >> N >> M >> A;
  if (A > N * M) {
    printf("IMPOSSIBLE");
  } else {
    int x = (A + M - 1) / M, y = x * M - A;
    printf("%d %d %d %d %d %d", 0, 0, x, y, 1, M);
  }
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
