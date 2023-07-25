#include <iostream>
#include <cstring>
using namespace std;

void sol() {
  const int MAX_SIZE = 20;
  enum { North = 1, East = 2 };
  struct Block {
    int S, W, T;
    int period;
    Block() {}
    Block(int s, int w, int t) : S(s), W(w), T(t) {
      period = S + W;
      T = (T % period) - period;
    }
    long long nextN(long long t) const {
      long long r = (t - T) % period;
      if (r <= S - 1) return t;
      return t + period - r;
    }
    long long nextE(long long t) const {
      long long r = (t - T) % period;
      if (r >= S && r <= period - 1) return t;
      if (r < S) return t + S - r;
      return t + period + S - r;
    }
  } blocks[MAX_SIZE][MAX_SIZE];

  int N, M; cin >> N >> M;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      int S, W, T; cin >> S >> W >> T;
      blocks[i][j] = {S, W, T};
    }
  }

  long long cost[MAX_SIZE][MAX_SIZE][4]; memset(cost, 1, sizeof(cost));
  cost[N - 1][0][0] = 0;
  for (;;) {
    bool changed = false;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        Block block = blocks[i][j];
        for (int d = 0; d < 4; d++) {
          long long t = cost[i][j][d];
          if (block.nextN(t) + 1 < cost[i][j][d ^ North]) {
            cost[i][j][d ^ North] = block.nextN(t) + 1;
            changed = true;
          }
          if (block.nextE(t) + 1 < cost[i][j][d ^ East]) {
            cost[i][j][d ^ East] = block.nextE(t) + 1;
            changed = true;
          }
          if (d & North) {
            if (i > 0 && t + 2 < cost[i - 1][j][d ^ North]) {
              cost[i - 1][j][d ^ North] = t + 2;
              changed = true;
            }
          } else {
            if (i < N - 1 && t + 2 < cost[i + 1][j][d ^ North]) {
              cost[i + 1][j][d ^ North] = t + 2;
              changed = true;
            }
          }
          if (d & East) {
            if (j < M - 1 && t + 2 < cost[i][j + 1][d ^ East]) {
              cost[i][j + 1][d ^ East] = t + 2;
              changed = true;
            }
          } else {
            if (j > 0 && t + 2 < cost[i][j - 1][d ^ East]) {
              cost[i][j - 1][d ^ East] = t + 2;
              changed = true;
            }
          }
        }
      }
    }
    if (!changed)
      break;
  }
  cout << cost[0][M - 1][North | East];
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
