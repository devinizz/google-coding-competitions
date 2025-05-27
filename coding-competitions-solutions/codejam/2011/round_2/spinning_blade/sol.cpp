#include <iostream>
using namespace std;

void sol() {
  const int MAX_N = 500;
  int R, C, D; cin >> R >> C >> D;
  int prefix_R[MAX_N][MAX_N] = {0,}, prefix_C[MAX_N][MAX_N] = {0,};
  for (int i = 0; i < R; i++) {
    string mass; cin >> mass;
    for (int j = 0; j < C; j++) {
      prefix_R[i][j + 1] = prefix_R[i][j] + mass[j] - '0';
      prefix_C[j][i + 1] = prefix_C[j][i] + mass[j] - '0';
    }
  }
  auto isValid = [&](int K) {
    for (int r = 0; r <= R - K; r++) {
      for (int c = 0; c <= C - K; c++) {
        int r_total = 0, c_total = 0;
        for (int i = 0; i < K; i++) {
          int edge = i == 0 | i == K - 1;
          int k = K - 1 - i * 2;
          r_total += (prefix_R[r + i][c + K - edge] - prefix_R[r + i][c + edge]) * k;
          c_total += (prefix_C[c + i][r + K - edge] - prefix_C[c + i][r + edge]) * k;
        }
        if (!r_total && !c_total)
          return true;
      }
    }
    return false;
  };
  for (int i = min(R, C); i >= 3; i--) {
    if (isValid(i)) {
      cout << i;
      return;
    }
  }
  cout << "IMPOSSIBLE";
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
