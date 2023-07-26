#include <iostream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

void sol() {
  int N, M; cin >> N >> M;
  struct Dir {
    map<string, Dir> child;
    int mkdir(string &path) {
      if (path.empty())
        return 0;
      auto it = find(path.begin() + 1, path.end(), '/');
      string name(path.begin() + 1, it);
      string left(it, path.end());
      return (child.find(name) == child.end()) + child[name].mkdir(left);
    }
  };
  Dir root;
  for (int i = 0; i < N; i++) {
    string s; cin >> s;
    root.mkdir(s);
  }
  int ans = 0;
  for (int i = 0; i < M; i++) {
    string s; cin >> s;
    ans += root.mkdir(s);
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
