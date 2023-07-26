#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <cmath>
using namespace std;

void sol() {
  int N, R; cin >> N >> R;
  int x[N + 1], y[N + 1];
  for (int i = 0; i < N; i++)
    cin >> x[i] >> y[i];
  x[N] = R; y[N] = 0;

  auto dist = [&](int a, int b) {
    long long dx = x[b] - x[a];
    long long dy = y[b] - y[a];
    return sqrt(dx * dx + dy * dy);
  };

  auto cross = [&](const pair<int, int>& d1, const pair<int, int>& d2) {
    long long x1 = x[d1.second] - x[d1.first];
    long long y1 = y[d1.second] - y[d1.first];
    long long x2 = x[d2.second] - x[d2.first];
    long long y2 = y[d2.second] - y[d2.first];
    return x1 * y2 - x2 * y1;
  };
  auto next = [&](int p, const pair<int, int>& d, double r) {
    r -= 0.9;
    vector<int> v;
    for (int i = 0; i < N; i++)
      if (i != p && dist(i, p) < r)
        v.push_back(i);

    return v.empty() ? -1 : *min_element(v.begin(), v.end(), [&](int a, int b) {
      if (cross(d, {p, a}) < 0 && cross(d, {p, b}) >= 0)
        return false;
      if (cross(d, {p, a}) >= 0 && cross(d, {p, b}) < 0)
        return true;

      return cross({p, a}, {p, b}) > 0 ||
             (cross({p, a}, {p, b}) == 0 && dist(p, a) > dist(p, b));
    });
  };

  map<pair<int, int>, int> dp;
  function<int(const pair<int, int>&)> get = [&](const pair<int, int>& p) {
    if (dp.find(p) != dp.end())
      return dp[p];
    int ret = 0;
    map<pair<int, int>, pair<double, int>> visit;
    int x = p.first;
    auto d = p;
    double len = dist(p.first, p.second);
    int count = 0;
    for (int n; (n = next(x, d, len)) != -1;) {
      ret = max(ret, count + get({x, n}));
      if (visit.find({x, n}) != visit.end()) {
        double dl = visit[{x, n}].first - len;
        int dc = count - visit[{x, n}].second;
        int t = (len - dl) / dl;
        len -= dl * t;
        count += dc * t;
        visit.erase({x, n});
      } else {
        visit[{x, n}] = {len, count};
        count++;
        len -= dist(x, n);
        d = {x, n};
        x = n;
      }
    }
    ret = max(ret, count);
    dp[p] = ret;
    return ret;
  };
  cout << get({0, N});
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
