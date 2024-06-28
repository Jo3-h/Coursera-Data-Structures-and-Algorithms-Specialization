#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

int distance(vector<vector<int> > &adj, int s, int t) {

  // if start or end are invalid return -1
  if (s < 0 || t < 0){
    return -1;
  }

  vector<int> dist(adj.size(), 2147483647);
  queue<int> q;
  dist[s] = 0;
  q.push(s);

  // while the queue is non-empty, search
  while (!q.empty()){
    int n = q.front();
    q.pop();
    for (int i=0; i<adj[n].size(); i++){
      int temp = adj[n][i];
      if (dist[temp] == 2147483647){
        q.push(temp);
        dist[temp] = dist[n] + 1;
      }
    }

  }

  if (dist[t] == 2147483647){
    return -1;
  } else {
    return dist[t];
  }
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, s, t);
}
