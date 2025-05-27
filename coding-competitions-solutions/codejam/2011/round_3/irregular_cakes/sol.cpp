#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

void sol() {
  struct Coord {
    double x, y;
    Coord(double x = 0, double y = 0): x(x), y(y) {}
  };
  static auto calc_h = [](const Coord& a, const Coord& b, double x) {
    return a.y + (b.y - a.y) / (b.x - a.x) * (x - a.x);
  };
  static auto calc_area = [](const Coord& a, const Coord& b) {
    return (b.y + a.y) * (b.x - a.x) / 2;
  };

  int W, L, U, G; cin >> W >> L >> U >> G;
  vector<Coord> lower(L), upper(U);
  for (auto &p: lower) cin >> p.x >> p.y;
  for (auto &p: upper) cin >> p.x >> p.y;
  vector<Coord> cake;
  for (int i = 0, j = 0; i != L && j != U;) {
    if (lower[i].x < upper[j].x) {
      cake.emplace_back(lower[i].x,
                        calc_h(upper[j - 1], upper[j], lower[i].x) - lower[i].y);
      i++;
    } else if (lower[i].x > upper[j].x) {
      cake.emplace_back(upper[j].x,
                        upper[j].y - calc_h(lower[i - 1], lower[i], upper[j].x));
      j++;
    } else {
      cake.emplace_back(lower[i].x, upper[j].y - lower[i].y);
      i++; j++;
    }
  }
  double area = 0;
  for (int i = 1; i < cake.size(); i++)
    area += calc_area(cake[i - 1], cake[i]);

  Coord cut = cake.front();
  for (int i = 1, j = 1; j < G; j++) {
    auto target = area / G;
    while (calc_area(cut, cake[i]) <= target) {
      target -= calc_area(cut, cake[i]);
      cut = cake[i++];
    }
    double begin = cut.x, end = cake[i].x;
    while (begin + 1e-9 < end) {
      double mid = (begin + end) / 2;
      if (calc_area(cut, Coord(mid, calc_h(cut, cake[i], mid))) <= target)
        begin = mid;
      else
        end = mid;
    }
    cut = {begin, calc_h(cut, cake[i], begin)};
    printf("%.7f\n", begin);
  }
}

int main() {
  int T; cin >> T;
  for (int case_num = 1; case_num <= T; case_num++) {
    cout << "Case #" << case_num << ":\n";

    sol();
  }
  return 0;
}
