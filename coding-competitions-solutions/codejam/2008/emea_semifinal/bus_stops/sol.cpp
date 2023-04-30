#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

template <class T>
T Exp(const T& x, int n) {
  if (n == 1) return x;
  if (n % 2 == 0) return Exp(x * x, n / 2);
  return Exp(x, n - 1) * x;
}

void sol() {
  struct Matrix {
    const int MOD = 30031;
    vector<vector<int>> mat;
    Matrix(int n) : mat(n, vector<int>(n)) {}
    Matrix operator*(const Matrix &v) const {
      Matrix tmp(mat.size());
      for (unsigned i = 0; i < mat.size(); i++)
        for (unsigned j = 0; j < mat.size(); j++)
          for (unsigned k = 0; k < mat.size(); k++)
            tmp.mat[i][j] = (tmp.mat[i][j] + mat[i][k] * v.mat[k][j]) % MOD;
      return tmp;
    }
  } A(0);
  vector<string> v;
  map<string, int> m;
  auto add = [&](string s) {
    if (m.find(s) == m.end()) {
      m[s] = m.size();
      v.push_back(s);
    }
  };
  int N, K, P; cin >> N >> K >> P;
  add(string(P - K, '0') + string(K, '1'));
  for (unsigned i = 0; i < v.size(); i++) {
    string s = string(v[i].begin() + 1, v[i].end()) + '1';
    vector<string> nxt;
    if (v[i][0] == '1') {
      nxt.push_back(s); add(s);
    } else {
      for (unsigned j = 0; j + 1 < s.size(); j++) {
        if (s[j] == '1') {
          s[j] = '0';
          nxt.push_back(s); add(s);
          s[j] = '1';
        }
      }
    }
    A.mat.resize(v.size());
    A.mat[i].resize(v.size());
    for (string s : nxt)
      A.mat[i][m[s]] += 1;
  }
  for (unsigned i = 0; i < v.size(); i++)
    A.mat[i].resize(v.size());
  cout << Exp(A, N - K).mat[0][0];
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
