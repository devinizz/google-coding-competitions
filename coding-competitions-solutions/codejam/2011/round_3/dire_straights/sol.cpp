#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

void sol() {
  int N; cin >> N;
  map<int, int> card;
  for (int i = 0; i < N; i++) {
    int c; cin >> c;
    card[c]++;
  }
  vector<int> seqs;
  int cur = 0; vector<int> seq;
  for (auto &it : card) {
    int c = cur == it.first - 1 ? it.second : 0;
    while (seq.size() > c) {
      seqs.push_back(seq.back()); seq.pop_back();
    }
    for (auto &s : seq)
      s++;
    while (seq.size() < it.second)
      seq.push_back(1);
    sort(seq.begin(), seq.end());
    cur = it.first;
  }
  seqs.insert(seqs.end(), seq.begin(), seq.end());
  if (!seqs.empty())
    cout << *min_element(seqs.begin(), seqs.end());
  else
    cout << 0;
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
