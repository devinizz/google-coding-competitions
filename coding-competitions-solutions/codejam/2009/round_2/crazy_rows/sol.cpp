#include <iostream>
#include <vector>
#include <string>
using namespace std;

void sol() {
  int N; cin >> N;
  vector<int> row(N);
  for (int &r : row) {
    string s; cin >> s;
    r = 0;
    for (int i = 0; i < N; i++)
      if (s[i] == '1')
        r = i;
  }
  int ans = 0;
  for (int i = 0; i < N; i++) {
    for (int j = i; j < N; j++) {
      if (row[j] <= i) {
        ans += j - i;
        while (j > i) {
          row[j] = row[j - 1];
          j--;
        }
        break;
      }
    }
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
