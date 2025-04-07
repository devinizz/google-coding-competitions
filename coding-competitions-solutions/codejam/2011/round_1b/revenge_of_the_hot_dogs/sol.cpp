#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

void sol() {
  struct Group {
    double start, end;
    double time;
    void move(double d) { start += d; end += d; time += abs(d); }
  };
  int C, D; cin >> C >> D;
  vector<Group> vendors;
  for (int i = 0; i < C; i++) {
    int P, V; cin >> P >> V;
    double t = 0.5 * D * (V - 1);
    vendors.push_back({P - t, P + t, t});
  }
  while (vendors.size() > 1) {
    auto v2 = vendors.back(); vendors.pop_back();
    auto v1 = vendors.back(); vendors.pop_back();
    double d = v2.start - v1.end;
    double t = v1.time - v2.time;
    if (d > D && t < 0) {
      v1.move(min(d - D, -t));
    } else if (d < D) {
      v1.move(t < 0 ? -min(D - d, -t) : 0);
      v2.move(t > 0 ? min(D - d, t) : 0);
      d = v2.start - v1.end;
      if (d < D) {
        v1.move((d - D) / 2);
        v2.move((D - d) / 2);
      }
    }
    vendors.push_back({v1.start, v2.end, max(v1.time, v2.time)});
  }
  printf("%.6lf", vendors.back().time);
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
