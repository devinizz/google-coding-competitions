#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string sub(const string &s1, const string &s2) {
  // This function requires s1 >= s2
  if (s1 == s2) return "0";
  string ret;
  int d = s1.size() - s2.size();
  bool borrow = false;
  for (int i = s1.size() - 1; i >= 0; i--) {
    char c = s1[i] - borrow; borrow = false;
    if (i >= d)
      c -= s2[i - d] - '0';
    if (c < '0') {
      borrow = true;
      c += 10;
    }
    ret = c + ret;
  }
  return ret.substr(ret.find_first_not_of('0'));
}

void sol() {
  const int MOD = 1e9 + 7;
  auto s2int = [&](const string &s) {
    int ret = 0;
    for (char c : s)
      ret = (10ll * ret + c - '0') % MOD;
    return ret;
  };
  auto exp10 = [&](int n) {
    int ret = 1;
    for (int i = 0; i < n; i++)
      ret = 10ll * ret % MOD;
    return ret;
  };
  auto calc = [&](const string &s) {
    int d = s.size();
    switch (d) {
      case 0: return 0;
      case 1: return (s2int(s) + 1) / 2;
      case 2: return s2int(s) / 22 * 11 + min(11, s2int(s) % 22 + 1) - 5;
      default:
        int ret = 50;
        for (int i = 4; i <= d; i++)
          ret = (ret + 45ll * exp10(i - i % 2 - 3) * (i % 2 * 10 + 1)) % MOD;

        string n = s.substr(0, (d + 1) / 2);
        int base = exp10((d - 1) / 2);
        string nn = n + string(n.rbegin() + (d % 2), n.rend());
        int step = (s2int(n) - base + MOD) % MOD;
        if ((n.back() - '0') % 2 == 1) {
          step += 1;
          if (s.compare(nn) < 0)
            ret = (ret - s2int(sub(nn, s)) + MOD + 1) % MOD;
        } else {
          if (s.compare(nn) >= 0)
            ret = (ret + s2int(sub(s, nn)) + 1) % MOD;
        }
        if (step % 2)
          step += MOD;
        int step_size = 1ll * base * ((d + 1) % 2 * 10 + 1) % MOD;
        ret = (ret + 1ll * step / 2 * step_size) % MOD;
        return ret;
    }
  };

  string L, R; cin >> L >> R;
  int even = (calc(R) - (L == "1" ? calc("0") : calc(sub(L, "2"))) + MOD) % MOD;
  int odd = (s2int(sub(R, L)) + 2 + MOD - even) % MOD;
  cout << (1ll * even * (even - 1) + 1ll * odd * (odd - 1)) / 2 % MOD;
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
