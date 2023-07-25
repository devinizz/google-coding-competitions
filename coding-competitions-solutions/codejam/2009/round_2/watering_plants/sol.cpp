#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
using namespace std;

void sol() {
  struct Plant {
    int X, Y, R;
  };
  int N; cin >> N;
  vector<Plant> plants(N);
  for (Plant &plant : plants)
    cin >> plant.X >> plant.Y >> plant.R;

  auto valid = [&](double r) {
    static auto cover = [&](double x, double y, double r) {
      long long ret = 0;
      for (int i = 0; i < N; i++) {
        double dx = plants[i].X - x;
        double dy = plants[i].Y - y;
        double r1 = r - plants[i].R;
        if (r1 >= 0 && dx * dx + dy * dy <= r1 * r1)
          ret |= 1ll << i;
      }
      return ret;
    };
    vector<long long> sprinkler(N);
    for (int i = 0; i < N; i++) {
      if (plants[i].R <= r)
        sprinkler.push_back(1ll << i);
      for (int j = i + 1; j < N; j++) {
        int dx = plants[j].X - plants[i].X;
        int dy = plants[j].Y - plants[i].Y;
        int len = dx * dx + dy * dy;
        double r1 = r - plants[i].R, r2 = r - plants[j].R;
        if (r1 > 0 && r2 > 0 && (r1 + r2) * (r1 + r2) >= len) {
          double s1 = ((r1 * r1 - r2 * r2) / len + 1) / 2;
          double s2 = sqrt(r1 * r1 / len - s1 * s1);
          double x = plants[i].X + s1 * dx;
          double y = plants[i].Y + s1 * dy;
          long long base = 1ll << i | 1ll << j;
          sprinkler.push_back(cover(x + s2 * dy, y - s2 * dx, r) | base);
          sprinkler.push_back(cover(x - s2 * dy, y + s2 * dx, r) | base);
        }
      }
    }
    for (unsigned i = 0; i < sprinkler.size(); i++)
      for (unsigned j = 0; j < i; j++)
        if ((sprinkler[i] | sprinkler[j]) == (1ll << N) - 1)
          return true;
    return false;
  };

  double low = 0, high = 1000;
  while (high - low > 1e-5) {
    double mid = (low + high) / 2;
    if (valid(mid))
      high = mid;
    else
      low = mid;
  }
  printf("%.6f", low);
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
