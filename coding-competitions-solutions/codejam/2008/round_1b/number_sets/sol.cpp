#include "../../../../../include/prime_sieve.hpp"
#include <iostream>
#include <vector>
using namespace std;

void sol() {
  static PrimeSieve primes(1e6);

  class DisjointSet {
   private:
    vector<int> size, parent;
    int find(int x) {
      if (parent[x] == x) return x;
      return parent[x] = find(parent[x]);
    }
   public:
    DisjointSet(int n) : size(n, 1), parent(n) {
      for (int i = 0; i < n; i++)
        parent[i] = i;
    }
    bool unite(int x, int y) {
      x = find(x), y = find(y);
      if (x == y) return false;
      if (size[x] <= size[y]) swap(x, y);
      parent[y] = x;
      size[x] += size[y];
      return true;
    }
  };

  long long A, B, P; cin >> A >> B >> P;
  int L = B - A + 1;

  DisjointSet ds(L);
  int ans = L;
  for (int prime : primes) {
    if (prime < P)
      continue;
    if (prime >= L)
      break;
    int n = (prime - (A % prime)) % prime;
    for (int i = n + prime; i < L; i += prime)
      ans -= ds.unite(n, i);
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
