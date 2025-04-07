#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
using namespace std;

void sol() {
  int N, M; cin >> N >> M;
  unordered_map<string, int> pos;
  unordered_map<string, unordered_map<char, int>> match;
  map<pair<int, int>, vector<string>> by_length;
  for (int i = 0; i < N; i++) {
    string s; cin >> s;
    pos[s] = i;
    by_length[{s.size(), 0}].push_back(s);
    for (char c = 'a'; c <= 'z'; c++) {
      int mask = 0;
      for (int j = 0; j < s.size(); j++) {
        if (s[j] == c)
          mask |= 1 << j;
      }
      match[s][c] = mask;
    }
  }

  for (int i = 0; i < M; i++) {
    string L; cin >> L;
    string ans;
    int cur = -1;
    auto groups = by_length;
    for (char c : L) {
      decltype(groups) nxt;
      int num = 0;
      for (auto& group : groups) {
        num += 1 << 10;
        if (group.second.size() == 1) {
          int cnt = group.first.second;
          if (cnt > cur ||
              cnt == cur && pos[group.second[0]] < pos[ans]) {
            cur = cnt;
            ans = group.second[0];
          }
          continue;
        }

        for (string& s : group.second) {
          int mask = match[s][c];
          nxt[{num | mask, group.first.second + (mask == 0)}].push_back(s);
        }
        if (nxt[{num, group.first.second + 1}].size() == group.second.size()) {
          nxt.erase({num, group.first.second + 1});
          nxt[{num, group.first.second}] = group.second;
        }
      }
      groups = std::move(nxt);
    }
    cout << " " << ans;
  }
}

int main() {
  int T; cin >> T;
  for (int case_num = 1; case_num <= T; case_num++) {
    cout << "Case #" << case_num << ":";

    sol();

    cout << '\n';
  }
  return 0;
}
