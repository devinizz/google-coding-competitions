#include <iostream>
#include <sstream>
#include <string>
#include <set>
#include <functional>
using namespace std;

void sol() {
  struct Tree {
    Tree *left = nullptr, *right = nullptr;
    double weight;
    string feature;
    ~Tree() { delete left; delete right; }
  };
  int L; cin >> L; cin.ignore();
  string describe;
  for (int i = 0; i < L; i++) {
    string s; getline(cin, s);
    describe += s + ' ';
  }
  function<Tree*(string& s)> get_tree;
  get_tree = [&](string &s) {
    s = s.substr(s.find('(') + 1);
    Tree *t = new Tree;
    istringstream iss(s);
    iss >> t->weight;
    if (s.find('(') < s.find(')')) {
      iss >> t->feature;
      t->left = get_tree(s);
      t->right = get_tree(s);
    }
    return t;
  };
  Tree *t = get_tree(describe);
  int A; cin >> A;
  for (int i = 0; i < A; i++) {
    string s; cin >> s;
    int n; cin >> n;
    set<string> features;
    for (int j = 0; j < n; j++) {
      cin >> s;
      features.insert(s);
    }
    double ans = 1;
    for (Tree *p = t; p;) {
      ans *= p->weight;
      if (features.find(p->feature) != features.end())
        p = p->left;
      else
        p = p->right;
    }
    printf("%.8f\n", ans);
  }
  delete t;
}

int main() {
  int T; cin >> T;
  for (int case_num = 1; case_num <= T; case_num++) {
    cout << "Case #" << case_num << ":\n";

    sol();
  }
  return 0;
}
