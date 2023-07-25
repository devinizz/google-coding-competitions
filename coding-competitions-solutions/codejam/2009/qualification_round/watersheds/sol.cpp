#include <iostream>
#include <vector>
#include <functional>
using namespace std;

void sol() {
  int H, W; cin >> H >> W;
  vector<vector<int>> altitudes(H, vector<int>(W));
  for (auto &v : altitudes)
    for (int &altitude : v)
      cin >> altitude;

  vector<vector<char>> basins(H, vector<char>(W));
  char cur = 'a';
  function<char(int, int)> get_basin;
  get_basin = [&](int i, int j) {
    static int dr[5] = {0, -1, 0, 0, 1};
    static int dc[5] = {0, 0, -1, 1, 0};
    if (basins[i][j]) return basins[i][j];
    int t = 0;
    for (int d = 1; d < 5; d++) {
      if (i + dr[d] < 0 || i + dr[d] >= H || j + dc[d] < 0 || j + dc[d] >= W)
        continue;
      if (altitudes[i + dr[d]][j + dc[d]] < altitudes[i + dr[t]][j + dc[t]])
        t = d;
    }
    if (t == 0)
      basins[i][j] = cur++;
    else
      basins[i][j] = get_basin(i + dr[t], j + dc[t]);

    return basins[i][j];
  };
  for (int i = 0; i < H; i++)
    for (int j = 0; j < W; j++)
      cout << get_basin(i, j) << (j == W - 1 ? '\n' : ' ');
}

int main() {
  int T; cin >> T;
  for (int case_num = 1; case_num <= T; case_num++) {
    cout << "Case #" << case_num << ":\n";

    sol();
  }
  return 0;
}
