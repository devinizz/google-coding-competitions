#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
  int L, D, N; cin >> L >> D >> N;
  vector<string> words(D);
  for (string &word : words)
    cin >> word;
  auto sol = [&]() {
    vector<string> patterns(L);
    for (string &pattern : patterns) {
      char c; cin >> c;
      if (c == '(') {
        for (;;) {
          cin >> c;
          if (c == ')')
            break;
          pattern += c;
        }
      } else {
        pattern = c;
      }
    }

    int ans = 0;
    for (string &word : words) {
      int i;
      for (i = 0; i < L; i++) {
        if (patterns[i].find(word[i]) == string::npos)
          break;
      }
      if (i == L)
        ans++;
    }
    cout << ans;
  };

  for (int case_num = 1; case_num <= N; case_num++) {
    cout << "Case #" << case_num << ": ";

    sol();

    cout << '\n';
  }
  return 0;
}
