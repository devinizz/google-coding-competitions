#include <iostream>
#include <vector>
#include <string>
using namespace std;

void sol() {
  string s; getline(cin, s);

  vector<int> dp(s.size(), 1);
  for (char c : string("welcome to code jam")) {
    vector<int> nxt(s.size());
    int last = 0;
    for (unsigned i = 0; i < dp.size(); i++) {
      nxt[i] = s[i] == c ? (last + dp[i]) % 10000 : last;
      last = nxt[i];
    }
    dp = move(nxt);
  }
  printf("%04d", dp.back());
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
