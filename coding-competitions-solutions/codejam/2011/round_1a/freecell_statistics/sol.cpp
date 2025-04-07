#include <iostream>
#include <numeric>
using namespace std;

void sol() {
  long long N; cin >> N;
  int P_D, P_G; cin >> P_D >> P_G;
  if (P_G == 0 && P_D > 0 ||
      P_G == 100 && P_D != 100 ||
      100 > gcd(P_D, 100) * N ) {
    cout << "Broken";
  } else {
    cout << "Possible";
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
