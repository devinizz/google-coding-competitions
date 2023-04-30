#include "../../../../../include/binary_indexed_tree.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void sol() {
  int N; cin >> N;
  struct Juice {
    int A, B, C;
    bool operator<(const Juice &v) const { return A < v.A; }
  };
  vector<Juice> juices(N);
  for (auto &juice : juices)
    cin >> juice.A >> juice.B >> juice.C;
  sort(juices.begin(), juices.end());
  int ans = 0;
  for (auto b : juices) {
    BinaryIndexedTree<int> bit(10001);
    for (auto juice : juices) {
      if (juice.A + b.B > 10000) break;
      if (juice.B <= b.B)
        bit.add(juice.C, 1);
      ans = max(ans, bit.prefix_sum(10000 - juice.A - b.B));
    }
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
