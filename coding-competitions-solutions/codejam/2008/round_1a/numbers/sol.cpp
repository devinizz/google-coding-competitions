#include <iostream>
#include <cstdio>
using namespace std;

template <class T>
T Exp(const T& x, int n) {
  if (n == 1) return x;
  if (n % 2 == 0) return Exp(x * x, n / 2);
  return Exp(x, n - 1) * x;
}

void sol() {
  struct Matrix {
    int mat[2][2] = {{3, 5}, {1, 3}};
    Matrix operator*(const Matrix &v) const {
      Matrix tmp;
      for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
          tmp.mat[i][j] = 0;
          for (int k = 0; k < 2; k++)
            tmp.mat[i][j] += this->mat[i][k] * v.mat[k][j];
          tmp.mat[i][j] %= 1000;
        }
      }
      return tmp;
    }
  };

  int n; cin >> n;
  printf("%03d", (2 * Exp(Matrix(), n).mat[0][0] + 999) % 1000);
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
