#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void sol() {
  int k; cin >> k;
  vector<vector<int>> axis[2]; axis[1].resize(2 * k - 1);
  for (int i = 1; i <= 2 * k - 1; i++) {
    axis[0].emplace_back(i > k ? 2 * k - i : i);
    int j = i > k ? i - k : k - i;
    for (int &x : axis[0].back()) {
      cin >> x;
      axis[1][j].push_back(x);
      j += 2;
    }
  }
  auto symmetry = [](vector<int> &v, int n) {
    int size = v.size() + abs(n);
    n = n < 0 ? 0 : n;
    for (int i = 0; i < (int)v.size(); i++) {
      int j = size - 1 - i - n - n;
      if (j > i && j < (int)v.size() && v[i] != v[j])
        return false;
    }
    return true;
  };
  int ans = 0;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 1000; j++) {
      if (all_of(axis[i].begin(), axis[i].end(), [&](vector<int> &v){
            return symmetry(v, j); })) {
        ans += j;
        break;
      } else if (all_of(axis[i].begin(), axis[i].end(), [&](vector<int> &v){
            return symmetry(v, -j); })) {
        ans += j;
        break;
      }
    }
  }
  cout << (2 * k + ans) * ans;
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
