#include <iostream>
#include <string>
using namespace std;

void sol() {
  const int SIZE = 3000;
  struct {
    int high = -SIZE, low = SIZE;
    bool is_valid() { return high > low; }
    void add(int y) {
      high = max(high, y);
      low = min(low, y);
    }
  } edge[SIZE * 2];

  int x = 0, y = 0;
  int x_step = 0, y_step = 1;
  int ans = 0;

  int L; cin >> L;
  string S; int T;
  for (int i = 0; i < L; i++) {
    cin >> S >> T;
    for (int t = 0; t < T; t++) {
      for (char c : S) {
        switch (c) {
          case 'F':
            if (x_step) {
              edge[min(x, x + x_step) + SIZE].add(y);
              ans += x_step * y;
            }
            x += x_step; y += y_step;
            break;
          case 'R':
            swap(x_step, y_step);
            y_step *= -1;
            break;
          case 'L':
            swap(x_step, y_step);
            x_step *= -1;
            break;
        }
      }
    }
  }
  ans = abs(ans);
  int hi = 0, li = 0;
  for (int i = 0; i < SIZE * 2; i++) {
    if (edge[i].high > edge[hi].high)
      hi = i;
    if (edge[i].low < edge[li].low)
      li = i;
  }
  auto f = [&edge, &ans](int x, int &y, bool h) {
    if (edge[x].is_valid()) {
      if (h) {
        y = max(y, edge[x].high);
        ans -= y;
      } else {
        y = min(y, edge[x].low);
        ans += y;
      }
    }
  };
  for (int i = 0, curr = -SIZE; i < hi; i++)
    f(i, curr, true);
  for (int i = SIZE * 2 - 1, curr = -SIZE; i >= hi; i--)
    f(i, curr, true);
  for (int i = 0, curr = SIZE; i < li; i++)
    f(i, curr, false);
  for (int i = SIZE * 2 - 1, curr = SIZE; i >= li; i--)
    f(i, curr, false);
  cout << -ans;
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
