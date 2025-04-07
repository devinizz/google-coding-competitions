#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

void sol() {
  int N; cin >> N;
  vector<int> C(N);
  for (int& c : C) cin >> c;
  if (accumulate(C.begin(), C.end(), 0, [](int a, int b) { return a ^ b; }) != 0)
    cout << "NO";
  else
    cout << accumulate(C.begin(), C.end(), 0) - *min_element(C.begin(), C.end());
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
