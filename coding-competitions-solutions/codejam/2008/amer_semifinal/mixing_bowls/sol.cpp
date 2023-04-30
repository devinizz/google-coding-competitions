#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <functional>
using namespace std;

void sol() {
  int N; cin >> N;
  map<string, vector<string>> ingredients;
  string recipe;
  for (int i = 0; i < N; i++) {
    string mixture; cin >> mixture;
    if (recipe.empty()) recipe = mixture;
    int M; cin >> M;
    for (int j = 0; j < M; j++) {
      string ingredient;
      cin >> ingredient;
      if (isupper(ingredient[0]))
        ingredients[mixture].push_back(ingredient);
    }
  }
  function<int(string)> count;
  count = [&](string mixture) {
    vector<int> r;
    for (string ingredient : ingredients[mixture])
      r.push_back(count(ingredient));
    if (r.empty()) return 1;
    sort(r.begin(), r.end(), greater<int>());
    for (unsigned i = 0; i < r.size(); i++)
      r[i] += i;
    sort(r.begin(), r.end(), greater<int>());
    return max(r[0], static_cast<int>(r.size()) + 1);
  };
  cout << count(recipe);
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
