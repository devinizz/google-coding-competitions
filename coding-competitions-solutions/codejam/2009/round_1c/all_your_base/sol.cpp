#include <iostream>
#include <string>
#include <map>
using namespace std;

void sol() {
  string s; cin >> s;
  map<char, int> m; m[s[0]] = 1;
  for (char c : s)
    if (m.find(c) == m.end())
      m[c] = m.size() == 1 ? 0 : m.size();
  long long ans = 0;
  for (char c : s) {
    ans *= m.size() < 2 ? 2 : m.size();
    ans += m[c];
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
