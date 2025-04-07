#include <iostream>
#include <string>
#include <vector>
using namespace std;

void sol() {
  struct Robot {
    int positon = 1;
    int time = 0;
    int press(int p, int t) {
      time = max(t, time + abs(p - positon)) + 1;
      positon = p;
      return time;
    }
  };

  Robot Orange, Blue;
  int N; cin >> N;
  int ans = 0;
  for (int i = 0; i < N; i++) {
    string R; cin >> R;
    int P; cin >> P;
    switch (R[0]) {
      case 'O': ans = Orange.press(P, ans); break;
      case 'B': ans = Blue.press(P, ans); break;
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
