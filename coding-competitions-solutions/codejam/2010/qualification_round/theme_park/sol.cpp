#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void sol() {
  int R, k, N; cin >> R >> k >> N;
  vector<int> g(N);
  for (int &x : g)
    cin >> x;

  vector<long long> sum(2 * N + 1);
  for (unsigned i = 1; i < sum.size(); i++)
    sum[i] = sum[i - 1] + g[(i - 1) % N];

  vector<int> visit(N);
  vector<long long> euros(N + 1);
  int pos = 0, t = 0;
  while (visit[pos] == 0) {
    visit[pos] = ++t;
    auto it = upper_bound(sum.begin(), sum.begin() + pos + N + 1, sum[pos] + k);
    euros[t] = euros[t - 1] + *prev(it) - sum[pos];
    pos = (it - sum.begin() - 1) % N;
  }

  if (R <= t) {
    cout << euros[R];
  } else {
    R -= t;
    int start = visit[pos] - 1;
    int n = t - start;
    long long c = euros[t] - euros[start];
    cout << euros[t] + (R / n) * c + euros[R % n + start] - euros[start];
  }
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
