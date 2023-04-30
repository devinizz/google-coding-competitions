#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void sol() {
  struct {
    vector<pair<int, int>> events;
    enum {
      ARRIVE,
      DEPART,
    };
    void Arrive(int t) { events.emplace_back(t, ARRIVE); }
    void Depart(int t) { events.emplace_back(t, DEPART); }

    int Calc() {
      int avail = 0, used = 0;
      sort(events.begin(), events.end());
      for (auto &event : events) {
        switch (event.second) {
          case ARRIVE: avail++; break;
          case DEPART:
            if (avail == 0) {
              used++;
              avail++;
            }
            avail--;
            break;
        }
      }
      return used;
    }
  } A, B;

  int T; cin >> T;
  int NA, NB; cin >> NA >> NB;
  for (int i = 0; i < NA; i++) {
    char c;
    int dep_hr, dep_min; cin >> dep_hr >> c >> dep_min;
    int arr_hr, arr_min; cin >> arr_hr >> c >> arr_min;
    A.Depart(dep_hr * 60 + dep_min);
    B.Arrive(arr_hr * 60 + arr_min + T);
  }
  for (int i = 0; i < NB; i++) {
    char c;
    int dep_hr, dep_min; cin >> dep_hr >> c >> dep_min;
    int arr_hr, arr_min; cin >> arr_hr >> c >> arr_min;
    B.Depart(dep_hr * 60 + dep_min);
    A.Arrive(arr_hr * 60 + arr_min + T);
  }

  cout << A.Calc() << ' ' << B.Calc();
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
