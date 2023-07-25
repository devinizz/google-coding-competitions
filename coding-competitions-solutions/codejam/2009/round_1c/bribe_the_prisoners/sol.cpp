#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
using namespace std;

void sol() {
  int P, Q; cin >> P >> Q;
  vector<int> prison(Q + 2);
  prison[0] = 0; prison[Q + 1] = P + 1;
  for (int i = 1; i <= Q; i++)
    cin >> prison[i];

  vector<vector<int>> memo(Q + 1, vector<int>(Q + 1));
  function<int(int, int)> find;
  find = [&](int a, int b) {
    if (a > b) return 0;
    if (memo[a][b]) return memo[a][b];
    int r = 1e9;
    int d = prison[b + 1] - prison[a - 1] - 2;
    for (int i = a; i <= b; i++)
      r = min(r, d + find(a, i - 1) + find(i + 1, b));
    memo[a][b] = r;
    return memo[a][b];
  };
  cout << find(1, Q);
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
