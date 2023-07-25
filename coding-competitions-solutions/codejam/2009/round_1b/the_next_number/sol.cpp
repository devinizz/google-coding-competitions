#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

void sol() {
  string N; cin >> N;
  N = '0' + N;
  next_permutation(N.begin(), N.end());
  if (N[0] == '0')
    cout << N.substr(1);
  else
    cout << N;
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
