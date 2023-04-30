#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <functional>
using namespace std;

void sol() {
  struct Tree {
    vector<int> depth;
    vector<vector<int>> node;
    Tree(vector<vector<int>> v, int r) : node(v.size()) {
      set<int> s;
      depth.push_back(r);
      for (unsigned i = 0; i < depth.size(); i++) {
        int n = depth[i];
        s.insert(n);
        for (int j : v[n]) {
          if (s.find(j) == s.end()) {
            depth.push_back(j);
            node[n].push_back(j);
          }
        }
      }
      reverse(depth.begin(), depth.end());
    }
    bool is_isomorphism(vector<vector<int>> v) {
      vector<vector<set<int>>> s(node.size(), vector<set<int>>(v.size()));
      auto is_match = [&](int n, int m) {
        vector<bool> visited(node.size());
        vector<int> from(node.size());
        vector<vector<int>> edge(v.size());
        int left = 0;
        function<bool(int)> dfs;
        dfs = [&](int s) {
          for (int d : edge[s]) {
            if (visited[d]) continue;
            visited[d] = true;
            if (from[d] == 0 || dfs(from[d])) {
              from[d] = s;
              return true;
            }
          }
          return false;
        };
        for (int i : v[m])
          for (int j : node[n])
            if (s[j][i].find(m) != s[j][i].end())
              edge[i].push_back(j);
        for (int i : v[m]) {
          fill(visited.begin(), visited.end(), false);
          if (!dfs(i)) {
            if (left)
              return false;
            left = i;
          }
        }
        if (left) {
          s[n][m].insert(left);
          fill(visited.begin(), visited.end(), false);
          dfs(left);
          for (int i : node[n])
            if (visited[i])
              s[n][m].insert(from[i]);
          return false;
        }
        return true;
      };
      for (int n : depth)
        for (unsigned m = 1; m < v.size(); m++)
          if (node[n].size() + 1 >= v[m].size() && is_match(n, m))
            return true;
      return false;
    }
  };
  int N; cin >> N;
  vector<vector<int>> large(N + 1);
  for (int i = 1; i < N; i++) {
    int a, b; cin >> a >> b;
    large[a].push_back(b);
    large[b].push_back(a);
  }
  int M; cin >> M;
  vector<vector<int>> small(M + 1);
  for (int i = 1; i < M; i++) {
    int a, b; cin >> a >> b;
    small[a].push_back(b);
    small[b].push_back(a);
  }
  cout << (Tree(large, 1).is_isomorphism(small) ? "YES" : "NO");
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
