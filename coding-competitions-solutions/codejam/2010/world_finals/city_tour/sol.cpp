#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

void sol() {
  int N; cin >> N;
  vector<pair<int, int>> points;
  points.emplace_back(1, 2);
  for (int i = 3; i < N; i++) {
    int p1, p2; cin >> p1 >> p2;
    if (p1 < p2)
      points.emplace_back(p1, p2);
    else
      points.emplace_back(p2, p1);
  }
  reverse(points.begin(), points.end());
  int ans = 0;
  map<pair<int, int>, pair<int, int>> count;
  for (auto &p : points) {
    int num = count[{p.first, N}].first
            + count[{p.second, N}].first + 1;
    auto &cur = count[{p.first, p.second}];
    if (num > cur.first) {
      cur.second = cur.first;
      cur.first = num;
    } else if (num > cur.second) {
      cur.second = num;
    }
    ans = max(ans, cur.first + cur.second + 2);
    N--;
  }
  cout << ans;
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
