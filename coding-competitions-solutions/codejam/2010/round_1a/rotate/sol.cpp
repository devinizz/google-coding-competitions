#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
using namespace std;

void sol() {
  int N, K; cin >> N >> K;
  vector<string> board(N);
  for (string &b : board) {
    cin >> b;
    b = {b.begin(), remove_if(b.begin(), b.end(),
        [](char c) { return c == '.'; })};
    reverse(b.begin(), b.end());
    b.resize(N, '.');
  }
  bool red = false, blue = false;
  vector<int> row(K); iota(row.begin(), row.end(), 0);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (board[i][j] == '.')
        continue;
      bool cur = false;
      if (all_of(row.begin(), row.end(), [&](int k)
            { return i + k < N && board[i][j] == board[i + k][j]; }))
        cur = true;
      if (all_of(row.begin(), row.end(), [&](int k)
            { return j + k < N && board[i][j] == board[i][j + k]; }))
        cur = true;
      if (all_of(row.begin(), row.end(), [&](int k)
            { return i + k < N && j + k < N && board[i][j] == board[i + k][j + k]; }))
        cur = true;
      if (all_of(row.begin(), row.end(), [&](int k)
            { return i + k < N && j - k >= 0 && board[i][j] == board[i + k][j - k]; }))
        cur = true;
      if (board[i][j] == 'B')
        blue |= cur;
      else
        red |= cur;
    }
  }
  if (red & blue)
    cout << "Both";
  else if (red)
    cout << "Red";
  else if (blue)
    cout << "Blue";
  else
    cout << "Neither";
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
