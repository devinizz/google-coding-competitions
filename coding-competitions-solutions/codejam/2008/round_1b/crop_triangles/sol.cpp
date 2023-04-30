#include <iostream>
using namespace std;

void sol() {
  int n, A, B, C, D; cin >> n >> A >> B >> C >> D;
  int x0, y0, M; cin >> x0 >> y0 >> M;

  int r[3][3] = {0,};
  for (int i = 0; i < n; i++) {
    r[x0 % 3][y0 % 3]++;
    x0 = (1ll * A * x0 + B) % M;
    y0 = (1ll * C * y0 + D) % M;
  }

  long long ans = 0;
  for (int x1 = 0; x1 < 3; x1++) {
    for (int y1 = 0; y1 < 3; y1++) {
      ans += 1ll * r[x1][y1] * (r[x1][y1] - 1) * (r[x1][y1] - 2);
      for (int x2 = 0; x2 < 3; x2++) {
        for (int y2 = 0; y2 < 3; y2++) {
          if (x1 == x2 && y1 == y2)
            continue;
          int x3 = (6 - x1 - x2) % 3;
          int y3 = (6 - y1 - y2) % 3;
          ans += 1ll * r[x1][y1] * r[x2][y2] * r[x3][y3];
        }
      }
    }
  }

  cout << ans / 6;
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
