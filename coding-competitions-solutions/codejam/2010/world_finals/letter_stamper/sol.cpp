#include <iostream>
#include <string>
using namespace std;

void sol() {
  string S; cin >> S;
  int ans = S.size();

  string st{S[0]};
  for (char c : S) {
    if (st.back() != c) {
      if (st.size() >= 2 && st[st.size() - 2] == c) {
        ans += 2;
        st.pop_back();
      } else {
        st.push_back(c);
      }
    }
  }
  cout << ans + (st.size() * 2 / 3 + 1) * 2;
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
