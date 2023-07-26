#include <iostream>
#include <vector>
using namespace std;

void sol() {
  int R; cin >> R;
  vector<int> X1(R), Y1(R), X2(R), Y2(R);
  for (int i = 0; i < R; i++)
    cin >> X1[i] >> Y1[i] >> X2[i] >> Y2[i];

  auto intersect = [&](int i, int j) {
    bool x_in = (X2[i] >= X1[j]) & (X2[j] >= X1[i]);
    bool y_in = (Y2[i] >= Y1[j]) & (Y2[j] >= Y1[i]);
    if (x_in && (y_in || Y2[i] + 1 == Y1[j] || Y2[j] + 1 == Y1[i]))
      return true;
    if (y_in && (x_in || X2[i] + 1 == X1[j] || X2[j] + 1 == X1[i]))
      return true;
    if ((X2[i] + 1 == X1[j] && Y2[j] + 1 == Y1[i]) ||
        (Y2[i] + 1 == Y1[j] && X2[j] + 1 == X1[i]))
      return true;
    return false;
  };

  int ans = 0;
  vector<bool> visited(R);
  for (int i = 0; i < R; i++) {
    if (visited[i]) continue;
    vector<int> group; group.push_back(i);
    for (;;) {
      bool changed = false;
      for (int j = i + 1; j < R; j++) {
        if (visited[j]) continue;
        for (int i : group) {
          if (intersect(i, j)) {
            visited[j] = changed = true;
            group.push_back(j);
            break;
          }
        }
      }
      if (!changed) break;
    }
    int xy_min = 1e7, x_max = 0, y_max = 0;
    for (int i : group) {
      xy_min = min(X1[i] + Y1[i], xy_min);
      x_max = max(X2[i], x_max);
      y_max = max(Y2[i], y_max);
    }
    ans = max(ans, x_max + y_max - xy_min + 1);
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
