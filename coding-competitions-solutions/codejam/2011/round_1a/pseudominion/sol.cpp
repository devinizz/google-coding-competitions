#include <iostream>
#include <numeric>
#include <vector>
#include <functional>
#include <map>
#include <algorithm>
using namespace std;

void sol() {
  struct Card {
    int c, s, t;
  };
  vector<int> T, C[3];
  vector<Card> deck;
  int N; cin >> N;
  int M = 0;
  for (int i = 0; i < N + M; i++) {
    Card card; cin >> card.c >> card.s >> card.t;
    if (card.t)
      T.push_back(deck.size());
    else
      C[card.c].push_back(deck.size());
    deck.push_back(card);
    if (i == N - 1)
      cin >> M;
  }
  function<int(int, int, int, int, int)> calc;
  map<tuple<int, int, int, int, int>, int> memo;
  calc = [&](int n, int turns, int t, int c1, int c2) {
    if (turns == 0)
      return 0;
    auto st = make_tuple(n, turns, t, c1, c2);
    if (memo.find(st) != memo.end())
      return memo[st];
    if (t < T.size() && T[t] < n) {
      Card& card = deck[T[t]];
      memo[st] = card.s + calc(n + card.c, turns + card.t - 1, t + 1, c1, c2);
    } else if (c2 < C[2].size() && C[2][c2] < n) {
      Card& card = deck[C[2][c2]];
      memo[st] = card.s + calc(n + card.c, turns - 1, t, c1, c2 + 1);
      memo[st] = max(memo[st], calc(n, turns, t, c1, c2 + 1));
    } else if (c1 < C[1].size() && C[1][c1] < n) {
      Card& card = deck[C[1][c1]];
      memo[st] = card.s + calc(n + card.c, turns - 1, t, c1 + 1, c2);
      memo[st] = max(memo[st], calc(n, turns, t, c1 + 1, c2));
    } else {
      vector<int> score;
      for (int i = 0; i < C[0].size() && C[0][i] < n; i++)
        score.push_back(deck[C[0][i]].s);
      sort(score.begin(), score.end(), greater<int>());
      turns = min(turns, static_cast<int>(score.size()));
      memo[st] = accumulate(score.begin(), score.begin() + turns, 0);
    }
    return memo[st];
  };
  cout << calc(N, 1, 0, 0, 0);
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
