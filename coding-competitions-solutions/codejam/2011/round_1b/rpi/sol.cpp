#include <iostream>
#include <vector>
#include <string>
using namespace std;

void sol() {
  struct Team {
    double OWP = 0;
    int win = 0;
    vector<int> opponents;
  };

  int N; cin >> N;
  vector<string> schedules(N);
  vector<Team> teams(N);
  for (int i = 0; i < N; i++) {
    cin >> schedules[i];
    for (int j = 0; j < N; j++) {
      switch (schedules[i][j]) {
        case '1':
          teams[i].win++;
        case '0':
          teams[i].opponents.push_back(j);
      }
    }
  }
  for (int i = 0; i < N; i++) {
    for (int opponent : teams[i].opponents) {
      int w = teams[opponent].win - (schedules[opponent][i] == '1');
      int o = teams[opponent].opponents.size() - 1;
      teams[i].OWP += 1.0 * w / o;
    }
    teams[i].OWP /= teams[i].opponents.size();
  }
  for (int i = 0; i < N; i++) {
    double ans = 0;
    for (int opponent : teams[i].opponents)
      ans += teams[opponent].OWP;
    ans = ans * 0.25 / teams[i].opponents.size();
    ans += 0.25 * teams[i].win / teams[i].opponents.size();
    ans += 0.5 * teams[i].OWP;
    cout << ans << endl;
  }
}

int main() {
  int T; cin >> T;
  for (int case_num = 1; case_num <= T; case_num++) {
    cout << "Case #" << case_num << ":\n";

    sol();
  }
  return 0;
}
