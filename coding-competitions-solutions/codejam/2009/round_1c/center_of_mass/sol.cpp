#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

void sol() {
  struct Point {
    double x, y, z;
    Point(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
    Point operator+(const Point &p) const {
      Point tmp(*this);
      tmp.x += p.x; tmp.y += p.y; tmp.z += p.z;
      return tmp;
    }
    Point operator*(double d) const {
      Point tmp(*this);
      tmp.x *= d; tmp.y *= d; tmp.z *= d;
      return tmp;
    }
    double dot(const Point &p) const { return x * p.x + y * p.y + z * p.z; }
    double len() const { return pow(dot(*this), 0.5); }
  };

  int N; cin >> N;
  Point p, v;
  for (int i = 0; i < N; i++) {
    double x, y, z, vx, vy, vz; cin >> x >> y >> z >> vx >> vy >> vz;
    p = p + Point(x, y, z);
    v = v + Point(vx, vy, vz);
  }
  p = p * (1e0 / N);
  v = v * (1e0 / N);
  double t = 0;
  if (v.len() != 0)
    t = max(t, -p.dot(v) / v.len() / v.len());
  printf("%.9f %.9f", (p + v * t).len(), t);
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
