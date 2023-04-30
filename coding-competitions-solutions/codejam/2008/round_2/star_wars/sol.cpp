#include <iostream>
#include <vector>
#include <algorithm>
#include <cfloat>
using namespace std;

void sol() {
  int N; cin >> N;
  struct Ship {
    int x, y, z, p;
    double dot(int a, int b, int c, double d) {
      return a * x + b * y + c * z + d * p;
    }
  };
  vector<Ship> ships(N);
  for (auto &ship : ships)
    cin >> ship.x >> ship.y >> ship.z >> ship.p;

  auto is_valid = [&ships](double power) {
    double a1, a2, b1, b2, c1, c2, d1, d2;
    a1 = b1 = c1 = d1 = -DBL_MAX;
    a2 = b2 = c2 = d2 = DBL_MAX;
    for (auto &ship : ships) {
      a1 = max(a1, ship.dot(-1, 1, 1, -power));
      a2 = min(a2, ship.dot(-1, 1, 1, power));
      b1 = max(b1, ship.dot(1, -1, 1, -power));
      b2 = min(b2, ship.dot(1, -1, 1, power));
      c1 = max(c1, ship.dot(1, 1, -1, -power));
      c2 = min(c2, ship.dot(1, 1, -1, power));
      d1 = max(d1, ship.dot(1, 1, 1, -power));
      d2 = min(d2, ship.dot(1, 1, 1, power));
    }
    return a1 < a2 && b1 < b2 && c1 < c2 && d1 < d2 &&
      d1 < a2 + b2 + c2 && a1 + b1 + c1 < d2;
  };

  double low = 0, high = 1e6 * 3;
  while (high - low > 1e-7) {
    double mid = (high + low) / 2;
    if (is_valid(mid))
      high = mid;
    else
      low = mid;
  }

  printf("%.6lf", low);
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
