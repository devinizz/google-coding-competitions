#include <iostream>
using namespace std;

void sol() {
  struct Coor {
    int x, y;
    Coor(int x = 0, int y = 0) : x(x), y(y) {}
    int len() const { return x * x + y * y; }
    Coor operator-(const Coor &c) const { return {x - c.x, y - c.y}; }
  };
  Coor coor[6];
  for (int i = 0; i < 6; i++)
    cin >> coor[i].x >> coor[i].y;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (j == i) continue;
      int k = 3 - i - j;
      Coor d1 = coor[j] - coor[i], d4 = coor[4] - coor[3];
      Coor d2 = coor[k] - coor[i], d5 = coor[5] - coor[3];
      Coor d3 = coor[k] - coor[j], d6 = coor[5] - coor[4];
      if (1ll * d1.len() * d5.len() == 1ll * d2.len() * d4.len() &&
          1ll * d1.len() * d6.len() == 1ll * d3.len() * d4.len()) {
        Coor a1 = d1 - d4;
        Coor a2 = d2 - d5;
        Coor b = coor[3] - coor[i];
        if (b.x == 0 && b.y == 0) {
          printf("%d %d", coor[i].x, coor[i].y);
        } else {
          if (a1.x == 0) {
            swap(a1.x, a1.y);
            swap(a2.x, a2.y);
            swap(b.x, b.y);
          }
          double k = 1e0 * a1.y / a1.x;
          double s2 = 1e0 * (b.x * k - b.y) / (a2.x * k - a2.y);
          double s1 = 1e0 * (b.x - s2 * a2.x) / a1.x;
          printf("%lf %lf", coor[i].x + s1 * d1.x + s2 * d2.x,
                            coor[i].y + s1 * d1.y + s2 * d2.y);
        }
        return;
      }
    }
  }
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
