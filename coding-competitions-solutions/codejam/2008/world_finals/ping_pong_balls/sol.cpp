#include <iostream>
#include <vector>
using namespace std;

void sol() {
  int W, H; cin >> W >> H;
  int dx1, dy1; cin >> dx1 >> dy1;
  int dx2, dy2; cin >> dx2 >> dy2;
  int x, y; cin >> x >> y;
  vector<bool> visited;
  auto inside = [&](int a, int b) {
    int xx = x + a * dx1 + b * dx2;
    int yy = y + a * dy1 + b * dy2;
    if (xx < 0 || xx >= W) return false;
    if (yy < 0 || yy >= H) return false;
    if (!visited.empty()) {
      if (visited[xx]) return false;
      visited[xx] = true;
    }
    return true;
  };
  if (dx1 * dy2 - dx2 * dy1 == 0) {
    vector<pair<int, int>> v; v.emplace_back(0, 0);
    visited.resize(W); visited[x] = true;
    for (unsigned i = 0; i < v.size(); i++) {
      int a = v[i].first, b = v[i].second;
      if (inside(a + 1, b))
        v.emplace_back(a + 1, b);
      if (inside(a, b + 1))
        v.emplace_back(a, b + 1);
    }
    cout << v.size();
  } else {
    long long ans = 0;
    int b1 = 0, b2 = 0;
    for (int a = 0; ; a++) {
      while (inside(a, b2)) b2++;
      while (!inside(a, b2) && b2 >= b1) b2--;
      while (!inside(a, b1) && b1 <= b2) b1++;
      if (b1 > b2) break;
      ans += b2 - b1 + 1;
    }
    cout << ans;
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
