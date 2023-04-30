#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
using namespace std;

int dr[4] = {-1, 0, 0, 1};
int dc[4] = {0, -1, 1, 0};
#define ADDR(i, j, d) i + dr[d]][j + dc[d]

void sol() {
  const int MAX_DAY = 50 * 50;
  int C, R, c, r; cin >> C >> R >> c >> r;
  vector<vector<int>> S(R + 2, vector<int>(C + 2));
  for (int i = 1; i <= R; i++)
    for (int j = 1; j <= C; j++)
      cin >> S[i][j];
  function<int(vector<vector<int>>, int)> dfs;
  dfs = [&](vector<vector<int>> S, int day) {
    auto nxtS(S);
    for (int i = 1; i <= R; i++) {
      for (int j = 1; j <= C; j++) {
        if ((i == r && j == c) || S[i][j] <= 0) continue;
        int target = 0;
        for (int k = 1; k < 4; k++)
          if (S[ADDR(i, j, k)] > S[ADDR(i, j, target)])
            target = k;
        nxtS[ADDR(i, j, target)] -= S[i][j];
      }
    }
    if (nxtS[r][c] <= 0) return day;
    int ret = -1;
    for (int d = 0; d < 4; d++) {
      if (nxtS[ADDR(r, c, d)] <= 0) continue;
      nxtS[ADDR(r, c, d)] -= S[r][c];
      ret = max(ret, dfs(nxtS, day + 1));
      nxtS[ADDR(r, c, d)] += S[r][c];
      if (ret == MAX_DAY)
        return MAX_DAY;
    }
    if (ret == -1) return MAX_DAY;
    return max(ret, dfs(nxtS, day + 1));
  };
  int days = dfs(S, 0);
  if (days == MAX_DAY)
    cout << "forever";
  else
    cout << days << " day(s)";
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
