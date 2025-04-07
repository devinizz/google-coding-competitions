#include <iostream>
#include <vector>
#include <string>
using namespace std;

void sol() {
  int R, C; cin >> R >> C;
  vector<string> picture(R);
  for (string &s : picture) cin >> s;

  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      if (picture[i][j] == '#') {
        if (i == R - 1 || j == C - 1 || picture[i + 1][j] != '#' ||
            picture[i][j + 1] != '#' || picture[i + 1][j + 1] != '#') {
          cout << "Impossible" << endl;
          return;
        }
        picture[i][j] = picture[i + 1][j + 1] = '/';
        picture[i + 1][j] = picture[i][j + 1] = '\\';
      }
    }
  }
  for (string &s : picture)
    cout << s << endl;
}

int main() {
  int T; cin >> T;
  for (int case_num = 1; case_num <= T; case_num++) {
    cout << "Case #" << case_num << ":\n";

    sol();
  }
  return 0;
}
