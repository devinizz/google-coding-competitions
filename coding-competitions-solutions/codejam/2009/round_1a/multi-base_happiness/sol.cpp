#include <iostream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

bool happy(int base, int n) {
  static const int MAX_BASE = 10;
  static const int MAX_SIZE = 1e7;
  static vector<vector<int>> memo(MAX_BASE + 1, vector<int>(MAX_SIZE, -1));
  if (n == 1) return 1;
  if (n >= MAX_SIZE || memo[base][n] == -1) {
    int nxt = 0;
    for (int m = n; m; m /= base)
      nxt += (m % base) * (m % base);

    if (n >= MAX_SIZE) return happy(base, nxt);
    memo[base][n] = 0; // loop means not happy
    memo[base][n] = happy(base, nxt);
  }
  return memo[base][n];
}

void sol() {
  string s; getline(cin, s);

  istringstream iss(s);
  vector<int> bases;
  for (int base; iss >> base;)
    bases.push_back(base);

  for (int n = 2;; n++) {
    unsigned i;
    for (i = 0; i < bases.size(); i++)
      if (!happy(bases[i], n))
        break;
    if (i == bases.size()) {
      cout << n;
      break;
    }
  }
}

int main() {
  int T; cin >> T; cin.ignore();
  for (int case_num = 1; case_num <= T; case_num++) {
    cout << "Case #" << case_num << ": ";

    sol();

    cout << '\n';
  }
  return 0;
}
