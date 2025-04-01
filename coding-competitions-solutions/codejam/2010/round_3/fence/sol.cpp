#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
using namespace std;

void sol() {
  long long L; int N; cin >> L >> N;
  vector<int> board(N);
  for (int &b : board) cin >> b;
  sort(board.begin(), board.end());
  int A = board.back();

  vector<int> d(A, A + 1); d[0] = 0;
  deque<int> dq; dq.push_back(0);
  while (!dq.empty()) {
    int n = dq.front(); dq.pop_front();
    for (int b : board) {
      int step = n + b < A;
      int nxt = (n + b) % A;
      if (d[n] + step < d[nxt]) {
        d[nxt] = d[n] + step;
        if (step)
          dq.push_back(nxt);
        else
          dq.push_front(nxt);
      }
    }
  }
  if (d[L % A] > A)
    cout << "IMPOSSIBLE";
  else
    cout << d[L % A] + L / A;
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
