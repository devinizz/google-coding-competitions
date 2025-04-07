#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

void sol() {
  int C; cin >> C;
  map<pair<char, char>, char> combine;
  for (int i = 0; i < C; i++) {
    string s;; cin >> s;
    combine[{s[0], s[1]}] = s[2];
    combine[{s[1], s[0]}] = s[2];
  }
  int D; cin >> D;
  map<char, vector<char>> clear;
  for (int i = 0; i < D; i++) {
    string s;; cin >> s;
    clear[s[0]].push_back(s[1]);
    clear[s[1]].push_back(s[0]);
  }
  int N; cin >> N;
  string s, ans; cin >> s;
  map<char, int> clear_count;
  for (char c : s) {
    if (!ans.empty() && combine.find({ans.back(), c}) != combine.end()) {
      for (char d : clear[ans.back()])
        clear_count[d]--;
      ans.back() = combine[{ans.back(), c}];
    } else if (clear_count[c]) {
      ans.clear();
      clear_count.clear();
    } else {
      ans.push_back(c);
      for (char d : clear[c])
        clear_count[d]++;
    }
  }
  cout << '[';
  for (int i = 0; i < ans.size(); i++) {
    if (i)
      cout << ", ";
    cout << ans[i];
  }
  cout << ']';
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
