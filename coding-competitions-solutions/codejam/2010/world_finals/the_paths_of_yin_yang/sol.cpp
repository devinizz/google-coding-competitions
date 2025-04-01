#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
#include <set>
#include <queue>
using namespace std;

void sol() {
  using Point = pair<int, int>;

  int N, M; cin >> N >> M;

  auto isValid = [N, M](const Point& p) {
    return p.first >= 0 && p.first < N && p.second >= 0 && p.second < M;
  };
  auto intersect = [&isValid](const vector<Point>& line1, const vector<Point>& line2) {
    set<Point> ret;
    for (auto& l1 : line1) {
      for (auto& l2 : line2) {
        int k_2 = l2.first + l2.second - l1.first - l1.second;
        if (k_2 % 2) continue;
        Point p(l1.first + k_2 / 2, l1.second + k_2 / 2);
        if (isValid(p))
          ret.insert(p);
      }
    }
    return vector<Point>(ret.begin(), ret.end());
  };

  static const int kMaxSize = 100;
  int board[kMaxSize][kMaxSize] = {0,};
  int dx[4] = {0, 1, 0, -1};
  int dy[4] = {1, 0, -1, 0};

  auto checkBoard = [&](const vector<Point>& endpoint) {
    auto isEndpoint = [&endpoint](const Point& p) {
      return find(endpoint.begin(), endpoint.end(), p) != endpoint.end();
    };
    int count = 0;
    vector<int> cur(board[0], board[0] + M);
    for (int i = 0; i < N; i++) {
      vector<int> nxt(M);
      for (int j = 0; j < M; j++) {
        int cnt = i == 0 ? 0 : cur[j] == board[i - 1][j];
        if (j > 0)
          cnt += (cur[j] == cur[j - 1]);
        if (j < M - 1)
          cnt += (cur[j] == cur[j + 1]);
        if (cnt > 2) return false;
        if (cnt == 2) {
          if (isEndpoint({i, j})) return false;
          nxt[j] = (cur[j] ^ 1);
        } else if (cnt == 1) {
          if (isEndpoint({i,j}))
            nxt[j] = (cur[j] ^ 1);
          else
            nxt[j] = cur[j];
        } else {
          if (!isEndpoint({i, j}))
            return false;
          nxt[j] = cur[j];
        }
      }
      if (i == N - 1) {
        for (int j = 0; j < M; j++) {
          if (cur[j] == nxt[j] || cur[j] != board[i][j])
            return false;
        }
      } else {
        if (cur[0] != board[i][0] || cur[M - 1] != board[i][M - 1])
          return false;
      }
      for (int j = 0; j < M; j++) {
        board[i][j] = cur[j];
        count += cur[j] == 0;
      }
      cur = std::move(nxt);
    }

    bool visited[kMaxSize][kMaxSize] = {0,};
    std::queue<Point> q;
    q.emplace(0, 1); visited[0][1] = true;
    while (!q.empty()) {
      auto p = q.front(); q.pop();
      count--;
      for (int i = 0; i < 4; i++) {
        int x = p.first + dx[i];
        int y = p.second + dy[i];
        if (!isValid({x, y})) continue;
        if (visited[x][y] || board[x][y]) continue;
        visited[x][y] = true;
        q.emplace(x, y);
      }
    }
    return any_of(endpoint.begin(), endpoint.end(), [&visited](const Point& p) { return visited[p.first][p.second]; }) && (count == 0);
  };

  vector<Point> outerloop;
  {
    int x = 0, y = 0;
    for (int i = 0; i < 4; i++) {
      while (isValid({x + dx[i], y + dy[i]})) {
        x += dx[i];
        y += dy[i];
        outerloop.emplace_back(x, y);
      }
    }
  }

  int ans = 0;
  vector<Point> line1(4), line2(4);
  line1[0] = {0, 0}; line1[1] = {N - 1, M - 1};
  line2[0] = {0, M - 1}; line2[1] = {N - 1, 0};
  for (int i = 0; i + 1 < outerloop.size(); i++) {
    memset(board, 0, sizeof(board));
    line1[2] = outerloop[i];
    line2[2] = outerloop[i + 1];
    if (line1[2].first == line2[2].first)
      swap(line1[2], line2[2]);
    for (int j = i + 1; j < outerloop.size(); j++) {
      board[outerloop[j].first][outerloop[j].second] = 1;
      line1[3] = outerloop[j];
      line2[3] = outerloop[j + 1 == outerloop.size() ? 0 : j + 1];
      if (line1[3].first == line2[3].first)
        swap(line1[3], line2[3]);

      auto endpoints = intersect(line1, line2);
      if (endpoints.size() < 4)
        continue;
      vector<bool> choose(endpoints.size(), false);
      fill(choose.end() - 4, choose.end(), true);
      do {
        vector<Point> endpoint;
        for (int k = 0; k < choose.size(); k++) {
          if (choose[k])
            endpoint.emplace_back(endpoints[k]);
        }
        ans += checkBoard(endpoint) * 2;
      } while (next_permutation(choose.begin(), choose.end()));
    }
  }

  cout << ans;
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
