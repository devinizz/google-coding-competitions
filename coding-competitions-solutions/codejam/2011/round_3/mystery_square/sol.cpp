#include <iostream>
#include <functional>
#include <boost/multiprecision/cpp_int.hpp>
using namespace std;

void sol() {
  using cpp_int = boost::multiprecision::cpp_int;
  string S; cin >> S;
  cpp_int base = 0, left = 0;
  vector<cpp_int> bag;
  for (int i = 0; i < S.size(); i++) {
    if (S[i] == '?') {
      bag.push_back(cpp_int(1) << S.size() - 1 - i);
      left += cpp_int(1) << S.size() - 1 - i;
    }
    base = (base << 1) + (S[i] == '1' ? 1 : 0);
  }
  function<cpp_int(cpp_int, cpp_int, int)> find = [&](cpp_int base, cpp_int left, int i) {
    cpp_int sq = sqrt(base);
    if (sq * sq == base)
      return base;
    cpp_int sq2 = sqrt(base + left);
    if (sq2 * sq2 == base + left)
      return (cpp_int)(base + left);
    if (sq == sq2)
      return (cpp_int)0;
    cpp_int ret = find(base + bag[i], left - bag[i], i + 1);
    if (ret)
      return ret;
    return find(base, left - bag[i], i + 1);
  };
  cpp_int ans = find(base, left, 0);
  string s;
  while (ans) {
    if (ans & 1)
      s += '1';
    else
      s += '0';
    ans >>= 1;
  }
  cout << string{s.rbegin(), s.rend()};
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
