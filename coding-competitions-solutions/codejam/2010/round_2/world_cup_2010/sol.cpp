#include <iostream>
#include <vector>
#include <functional>
using namespace std;

void sol() {
  int P; cin >> P;
  vector<int> node((2 << P) - 1);
  for (auto it = node.rbegin(); it != node.rend(); it++)
    cin >> *it;

  vector<vector<long long>> memo(node.size(), vector<long long>(P + 1, -1));
  function<long long(int, int)> dp;
  dp = [&](int i, int j) {
    if (memo[i][j] >= 0) return memo[i][j];
    if (i >= (1 << P) - 1)
      memo[i][j] = j + node[i] >= P ? 0 : 1e9;
    else
      memo[i][j] = min(node[i] + dp(i * 2 + 1, j + 1) + dp(i * 2 + 2, j + 1),
          dp(i * 2 + 1, j) + dp(i * 2 + 2, j));
    return memo[i][j];
  };

  cout << dp(0, 0);
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
