#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void sol() {
  const int SIZE = 256;
  int D, I, M, N; cin >> D >> I >> M >> N;
  vector<int> pixels(N);
  for (int &pixel : pixels)
    cin >> pixel;

  vector<int> dp(SIZE);
  for (int pixel : pixels) {
    vector<int> cur(SIZE);
    for (int i = 0; i < SIZE; i++) {
      int diff = abs(pixel - i);
      cur[i] = dp[i] + min(D, diff);
      if (M == 0)
        continue;
      for (int j = 0; j < SIZE; j++)
        if (i != j)
          cur[i] = min(cur[i], dp[j] + diff + (abs(i - j) - 1) / M * I);
    }
    dp = move(cur);
  }
  cout << *min_element(dp.begin(), dp.end());
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
