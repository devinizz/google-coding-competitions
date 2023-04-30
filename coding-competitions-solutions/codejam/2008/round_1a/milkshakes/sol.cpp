#include <iostream>
#include <vector>
using namespace std;

void sol() {
  int N; cin >> N;
  struct {
    bool is_malted = false;
    vector<int> unmalted;
  } milkshake[N + 1];

  int M; cin >> M;
  struct {
    int count = 0;
    int malted_flavor = 0;
  } customer[M];

  vector<int> unhappy;
  for (int m = 0; m < M; m++) {
    int T; cin >> T;
    for (int i = 0; i < T; i++) {
      int X, Y; cin >> X >> Y;
      if (Y == 0) {
        milkshake[X].unmalted.push_back(m);
        customer[m].count++;
      } else {
        customer[m].malted_flavor = X;
      }
    }
    if (customer[m].count == 0)
      unhappy.push_back(m);
  }

  for (int i = 0; i < unhappy.size(); i++) {
    int m = unhappy[i];
    int x = customer[m].malted_flavor;
    if (x == 0) {
      cout << "IMPOSSIBLE";
      return;
    }
    if (milkshake[x].is_malted == false) {
      milkshake[x].is_malted = true;
      for (auto c : milkshake[x].unmalted) {
        customer[c].count--;
        if (customer[c].count == 0)
          unhappy.push_back(c);
      }
    }
  }

  for (int i = 1; i <= N; i++)
    cout << milkshake[i].is_malted << (i < N ? " " : "");
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
