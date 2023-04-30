#include "../../../../../include/binary_indexed_tree.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void sol() {
  int n, m, X, Y, Z; cin >> n >> m >> X >> Y >> Z;
  vector<int> A(m); for (int &x : A) cin >> x;
  vector<int> speed(n);
  for (int i = 0; i < n; i++) {
    speed[i] = A[i % m];
    A[i % m] = (1ll * X * A[i % m] + 1ll * Y * (i + 1)) % Z;
  }
  vector<int> sorted(speed); sort(sorted.begin(), sorted.end());
  for (int &s : speed)
    s = lower_bound(sorted.begin(), sorted.end(), s) - sorted.begin();

  struct Mod {
    const int MOD = 1e9 + 7;
    int value;
    operator int() const { return value; }
    Mod(int n = 0) : value(n) {}
    Mod& operator+=(const Mod& m) {
      this->value = (this->value + m.value) % MOD;
      return *this;
    }
  };
  BinaryIndexedTree<Mod> bit(speed.size());
  for (int s : speed)
    bit.add(s, (s > 0 ? bit.prefix_sum(s - 1) : Mod(0)) + 1);
  cout << bit.prefix_sum(speed.size() - 1);
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
