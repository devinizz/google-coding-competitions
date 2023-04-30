#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

static inline double square(double x) { return x * x; }
static inline double calc(double c, double a) {
  return c > a ? sqrt(square(c) - square(a)) : 0;
}
static inline double circle_segment(double r, double th) {
  return square(r) * (th - sin(th)) / 2;
}

void sol() {
  double f, R, t, r, g; cin >> f >> R >> t >> r >> g;
  double area = M_PI * square(R) / 4;
  R -= t + f; r += f; g -= f * 2;
  if (g <= 0) {
    printf("%.6f", 1.);
    return;
  }

  double sum = 0;
  double step = 2 * r + g;
  for (double x = r; x < calc(R, r); x += step) {
    int n = static_cast<int>((calc(R, x + g) - r) / step);
    sum += n * square(g);

    for (double y = r + n * step; y < calc(R, x); y += step) {
      double x2 = x + g;
      double y2 = y + g;
      if (x2 < calc(R, y2)) {
        sum += square(g);
      } else if (x < calc(R, y2) && y < calc(R, x2)) {
        sum += circle_segment(R, asin(y2 / R) - acos(x2 / R));
        sum += square(g);
        sum -= (y2 - calc(R, x2)) * (x2 - calc(R, y2)) / 2;
      } else if (x < calc(R, y2)) {
        sum += circle_segment(R, asin(y2 / R) - asin(y / R));
        sum += g * (calc(R, y) - x + calc(R, y2) - x) / 2;
      } else if (y < calc(R, x2)) {
        sum += circle_segment(R, acos(x / R) - acos(x2 / R));
        sum += g * (calc(R, x) - y + calc(R, x2) - y) / 2;
      } else {
        sum += circle_segment(R, acos(x / R) - asin(y / R));
        sum += (calc(R, x) - y) * (calc(R, y) - x) / 2;
      }
    }
  }

  printf("%.6lf", 1 - sum / area);
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
