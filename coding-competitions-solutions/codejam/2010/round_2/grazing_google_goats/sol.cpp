#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
using namespace std;

template <class T> T pow(T x) { return x * x; }

void sol() {
  auto deg = [&](int dx, int dy) {
    double rad = acos(dx / sqrt(pow(dx) + pow(dy)));
    return dy > 0 ? rad : 2 * M_PI - rad;
  };

  int N, M; cin >> N >> M;
  vector<int> Px(N), Py(N);
  for (int i = 0; i < N; i++)
    cin >> Px[i] >> Py[i];

  for (int i = 0; i < M; i++) {
    int Qx, Qy;
    cin >> Qx >> Qy;
    vector<double> rad(N);
    for (int i = 0; i < N; i++)
      rad[i] = deg(Px[i] - Qx, Py[i] - Qy);

    auto comp = [&](int a, int b) { return rad[a] < rad[b]; };

    vector<int> order(N); iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), comp);
    if (rad[order.back()] - rad[order[0]] > M_PI) {
      for (double &r : rad)
        r = r > M_PI ? r - 2 * M_PI : r;
      sort(order.begin(), order.end(), comp);
    }

    double from = rad[order.back()] - M_PI / 2;
    double to = rad[order[0]] + M_PI / 2;
    if (from >= to) {
      cout << " 0.0";
      continue;
    }

    vector<pair<double, int>> area;
    for (int n : order) {
      for (;;) {
        if (area.empty()) {
          area.emplace_back(to, n);
          break;
        }
        auto &t = area.back();
        double r = M_PI / 2 + deg(Px[t.second] - Px[n],
                                  Py[t.second] - Py[n]);
        r = abs(r - t.first) > M_PI ? r - 2 * M_PI : r;
        if (r < from)
          break;
        if (r < t.first) {
          area.emplace_back(r, n);
          break;
        }
        area.pop_back();
      }
    }
    double ans = 0;
    for (auto it = area.rbegin(); it != area.rend(); it++) {
      int n = it->second;
      double b = M_PI / 2 - abs(from - rad[n]);
      double c = M_PI / 2 - abs(it->first - rad[n]);
      double a = it->first - from; from = it->first;
      double r = sqrt(pow(Qx - Px[n]) + pow(Qy - Py[n]));
      ans += pow(r) * a - pow(r) * sin(2 * a) / 2;
      ans += 2 * pow(r) * sin(a) * sin(b) * sin(c);
    }
    printf(" %.7f", ans);
  }
}

int main() {
  int T; cin >> T;
  for (int case_num = 1; case_num <= T; case_num++) {
    cout << "Case #" << case_num << ":";

    sol();

    cout << '\n';
  }
  return 0;
}
