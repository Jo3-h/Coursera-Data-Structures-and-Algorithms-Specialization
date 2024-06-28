#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;
using std::make_pair;

typedef pair<long long, int> node;

long long distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t) {
  
  // create priority queue 
  priority_queue<pair<long long, int> > pq;

  // create distances vector
  vector<long long> dist(adj.size(), 9223372036854775807);

  // add the source to the priority queue
  pq.push(make_pair(0, s));
  dist[s] = 0;

  while (!pq.empty()){

    int cur = pq.top().second;
    pq.pop();

    for (int i=0; i<adj[cur].size(); i++){

      int next = adj[cur][i];
      long long temp = cost[cur][i];

      if (dist[next] > dist[cur] + temp){
        dist[next] = dist[cur] + temp;
        pq.push(make_pair(dist[next]*(-1), next));
      }


    }


  }
  if (dist[t] == 9223372036854775807){
    return -1;
  } else {
    return dist[t];
  }

  return -1;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, cost, s, t);
}
