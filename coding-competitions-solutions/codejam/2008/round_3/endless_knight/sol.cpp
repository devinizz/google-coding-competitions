#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int ExpMod(int n, int k, int m) {
  if (k == 1) return n % m;
  if (k % 2 == 0) return ExpMod(n * n % m, k / 2, m);
  return ExpMod(n, k - 1, m) * n % m;
}
inline int inv(int n, int p) { return ExpMod(n, p - 2, p); }

void sol() {
  const int MOD = 10007;
  int H, W, R; cin >> H >> W >> R;
  struct Coor {
    int h, w, sum;
    Coor(int h = 0, int w = 0, int sum = 0) : h(h), w(w), sum(sum) {}
    bool operator<(const Coor& c) const { return h + w < c.h + c.w; }
    void add(const Coor& c) {
      if ((h + w - c.h - c.w) % 3 != 0) return;
      int n = (h + w - c.h - c.w) / 3;
      int k = (h - c.h - n);
      if (k < 0 || k > n) return;
      long long prod = 1;
      for (int i = 0; i < k % MOD; i++) {
        prod = prod * (n - i) % MOD;
        prod = prod * inv(i + 1, MOD) % MOD;
      }
      for (int i = 0, p = n / MOD; i < k / MOD; i++) {
        prod = prod * (p - i) % MOD;
        prod = prod * inv(i + 1, MOD) % MOD;
      }
      sum = (sum + prod * c.sum) % MOD;
    }
  };
  vector<Coor> rocks(R);
  for (auto &rock : rocks)
    cin >> rock.h >> rock.w;
  sort(rocks.begin(), rocks.end());
  rocks.emplace_back(H, W);
  for (auto &rock : rocks) {
    rock.add(Coor(1, 1 ,1));
  }
  for (unsigned i = 0; i < rocks.size() - 1; i++) {
    rocks[i].sum = (MOD - rocks[i].sum) % MOD;
    for (unsigned j = i + 1; j < rocks.size(); j++)
      rocks[j].add(rocks[i]);
  }
  cout << rocks.back().sum;
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
