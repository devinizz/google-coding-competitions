#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <cstring>
using namespace std;

void sol() {
  const int MAX_SIZE = 50;
  int R, C, F; cin >> R >> C >> F;
  vector<string> cave(R);
  for (string &s : cave)
    cin >> s;
  cave.emplace_back(C, '#');

  static int memo[MAX_SIZE][MAX_SIZE][MAX_SIZE][MAX_SIZE];
  memset(memo, 0, sizeof(memo));
  function<int(int, int, int, int)> find;
  find = [&](int i, int j, int l, int r) {
    if (i == R - 1) return 1; // 0 means unvisited
    if (memo[i][j][l][r]) return memo[i][j][l][r];

    int ret = MAX_SIZE * MAX_SIZE;
    int h = 0;
    while (cave[i + h + 1][j] == '.')
      h++;
    if (h) {
      if (h < F)
        ret = find(i + h, j, j, j);
      memo[i][j][l][r] = ret;
      return ret;
    }

    int p1, p2;
    for (p1 = j - 1; p1 >= 0; p1--) {
      if ((cave[i][p1] == '#' && p1 < l))
        break;
      if (cave[i + 1][p1] == '.') {
        ret = min(ret, find(i + 1, p1, p1, p1));
        break;
      }
    } p1 += 1;
    for (p2 = j + 1; p2 < C; p2++) {
      if ((cave[i][p2] == '#' && p2 > r))
        break;
      if (cave[i + 1][p2] == '.') {
        ret = min(ret, find(i + 1, p2, p2, p2));
        break;
      }
    } p2 -= 1;
    if (p1 != p2) {
      ret = min(ret, 1 + find(i + 1, p1, p1, p1));
      ret = min(ret, 1 + find(i + 1, p2, p2, p2));

      for (int p = p1 + 1; p < p2; p++) {
        for (int d = p1; d <= p; d++)
          ret = min(ret, p - d + 1 + find(i + 1, p, d, p));
        for (int d = p; d <= p2; d++)
          ret = min(ret, d - p + 1 + find(i + 1, p, p, d));
      }
    }
    memo[i][j][l][r] = ret;
    return memo[i][j][l][r];
  };

  int ans = find(0, 0, 0, 0);
  if (ans >= MAX_SIZE * MAX_SIZE)
    cout << "No";
  else
    cout << "Yes " << ans - 1;
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
