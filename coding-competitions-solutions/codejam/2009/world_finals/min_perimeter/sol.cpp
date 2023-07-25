#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cmath>
using namespace std;

void sol() {
  using Point = pair<int, int>;
  int n; cin >> n;
  vector<Point> points(n);
  for (Point &point : points)
    cin >> point.first >> point.second;
  sort(points.begin(), points.end());

  function<double(Point *p, int n)> calc;
  calc = [&calc](Point *p, int n) {
    static auto perimeter = [](const Point &a, const Point &b, const Point &c) {
      static auto dist = [](const Point &a, const Point &b) {
        static auto square = [](int n) { return 1ll * n * n; };
        return sqrt(square(a.first - b.first) + square(a.second - b.second));
      };
      return dist(a, b) + dist(b, c) + dist(a, c);
    };

    double ret = 1e10;
    if (n < 6) {
      for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
          for (int k = j + 1; k < n; k++)
            ret = min(ret, perimeter(p[i], p[j], p[k]));
    } else {
      ret = min(ret, calc(p, n / 2));
      ret = min(ret, calc(p + n / 2, (n + 1) / 2));
      auto left = lower_bound(p, p + n, Point(p[n / 2].first - ret / 2, 0));
      auto right = upper_bound(p, p + n, Point(p[n / 2].first + ret / 2, 0));
      vector<Point> points(left, right);
      sort(points.begin(), points.end(), [](const Point &a, const Point &b) {
          return a.second < b.second;
      });
      unsigned start = 0;
      for (unsigned i = 0; i < points.size(); i++) {
        while (points[start].second + ret / 2 < points[i].second) start++;
        for (unsigned j = start; j < i; j++)
          for (unsigned k = j + 1; k < i; k++)
            ret = min(ret, perimeter(points[i], points[j], points[k]));
      }
    }
    return ret;
  };
  printf("%.6f", calc(points.data(), n));
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
