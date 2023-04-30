#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAX_SIZE = 15;
int memo[MAX_SIZE][MAX_SIZE][1 << (MAX_SIZE + 1)];
vector<string> grid(MAX_SIZE);
int R, C;

int dp(int r, int c, int b) {
  if (c == C) {
    c = 0;
    if (++r == R) return 0;
  }
  int& ret = memo[r][c][b];
  if (ret != -1) return ret;
  int b2 = (b << 1) & ((1 << (C + 1)) - 1);
  if (grid[r][c] != '.') {
    ret = dp(r, c + 1, b2);
  } else {
    ret = dp(r, c + 1, b2 + 1);
    if (c && b & 1)
      ret = max(ret, 1 + dp(r, c + 1, b2 ^ 2));
    if (c && b & (1 << C))
      ret = max(ret, 1 + dp(r, c + 1, b2));
    if (b & (1 << (C - 1)))
      ret = max(ret, 1 + dp(r, c + 1, b2 ^ (1 << C)));
    if (c < C - 1 && b & (1 << (C - 2)))
      ret = max(ret, 1 + dp(r, c + 1, b2 ^ (1 << (C - 1))));
  }
  return ret;
}

void sol() {
  int KR, KC;
  cin >> R >> C;
  for (int r = 0; r < R; r++) {
    cin >> grid[r];
    auto c = grid[r].find('K');
    if (c != string::npos) {
      KR = r; KC = c;
    }
  }
  memset(memo, -1, sizeof(memo));
  int m1 = dp(0, 0, 0);
  memset(memo, -1, sizeof(memo));
  grid[KR][KC] = '.';
  int m2 = dp(0, 0, 0);
  cout << (m2 > m1 ? "A" : "B");
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
