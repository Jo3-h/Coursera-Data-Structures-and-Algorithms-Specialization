#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

int search(vector<vector<int> > &adj, vector<int> &col, int source){

  queue<int> q;
  q.push(source);
  col[source] = 0;

  // perform bfs on graph
  while(!q.empty()){

    // inspect the first node in the queue
    int temp = q.front();
    q.pop();

    // loop through all neighbours of the node
    for (int i=0; i<adj[temp].size(); i++){
      int n = adj[temp][i];

      if (n == temp){
        return 1;
      }

      // if the node hasn't been searched then add to the queue and set let
      if (col[n] == -1){
        q.push(n);
        col[n] = 1 - col[temp];
        continue;
      } 

      if (col[n] == col[temp]){
        return 1;
      }

    }
  }

  return 0;
}

int bipartite(vector<vector<int> > &adj) {
  //write your code here
  if (!adj.size()){
    return -1;
  }

  vector<int> col(adj.size(), -1);
  int res = 0;

  for (int i=0; i<adj.size(); i++){
    if (col[i] == -1){
      res = search(adj, col, i);
      if (res){
        return 0;
      }
    }
  }
  return 1;
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
  std::cout << bipartite(adj);
}
