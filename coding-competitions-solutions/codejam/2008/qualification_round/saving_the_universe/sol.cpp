#include <iostream>
#include <set>
#include <string>
using namespace std;

void sol() {
  string name;
  int count = 0;
  set<string> visited;

  int S; cin >> S; cin.ignore();
  for (int i = 0; i < S; i++)
    getline(cin, name);

  int Q; cin >> Q; cin.ignore();
  for (int i = 0; i < Q; i++) {
    getline(cin, name);
    visited.insert(name);
    if (static_cast<int>(visited.size()) == S) {
      count++;
      visited.clear();
      visited.insert(name);
    }
  }
  cout << count;
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
