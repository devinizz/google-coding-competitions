#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

void sol() {
  int N; cin >> N;
  vector<long long> X(N); for (auto &x : X) cin >> x;
  long long F; cin >> F;
  F /= 2;
  sort(X.begin(), X.end());
  if (X.back() - X.front() > F) {
    cout << "NO SOLUTION";
    return;
  }
  if (N < 4) {
    cout << (X.back() - X.front()) * 2;
    return;
  }
  int mid = N / 2;
  auto find = [&](int begin, int end, int step) {
    vector<set<long long>> dp(mid + 2);
    dp[1].insert(X[begin + 1] - X[begin]);
    for (int i = begin + step; i != end; i += step) {
      vector<set<long long>> cur(mid + 2);
      for (int j = 1; j <= mid; j++) {
        for (auto &x : dp[j]) {
          cur[j - 1].insert(x + (X[i + 1] - X[i]) * (j - 1));
          cur[j].insert(x + (X[i + 1] - X[i]) * j);
          cur[j + 1].insert(x + (X[i + 1] - X[i]) * (j + 1));
        }
      }
      dp = std::move(cur);
    }
    return dp;
  };
  long long ans = 0;
  auto left = find(0, mid, 1);
  auto right = find(N - 2, mid - 2, -1);
  for (int i = 1; i <= mid; i++) {
    auto it = right[i].rbegin();
    auto overlap = (X[mid] - X[mid - 1]) * i;
    for (auto &x : left[i]) {
      while (x + *it - overlap > F && it != right[i].rend())
        it++;
      if (it == right[i].rend())
        break;
      ans = max(ans, x + *it - overlap);
    }
  }
  cout << ans * 2;
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
