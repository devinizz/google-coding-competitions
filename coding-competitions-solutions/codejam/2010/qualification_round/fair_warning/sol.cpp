#include <algorithm>
#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
#include <numeric>
using namespace std;

void sol() {
  using cpp_int = boost::multiprecision::cpp_int;
  int N; cin >> N;
  vector<cpp_int> t(N); for (auto &t_i : t) cin >> t_i;
  auto t_min = *min_element(t.begin(), t.end());
  transform(t.begin(), t.end(), t.begin(),
      [&t_min](cpp_int t_i) { return t_i - t_min; });
  auto divisor = accumulate(t.begin(), t.end(), cpp_int(0),
      [](cpp_int a, cpp_int b) { return gcd(a, b); });
  t_min %= divisor;
  cout << (t_min ? divisor - t_min : cpp_int(0));
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
