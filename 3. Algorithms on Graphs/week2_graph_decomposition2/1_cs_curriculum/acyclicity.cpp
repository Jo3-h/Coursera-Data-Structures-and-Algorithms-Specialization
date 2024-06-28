#include <iostream>
#include <vector>

using std::vector;
using std::pair;

void del(vector<vector<int> > &adj, int i){
  while (adj[i].size()){
    adj[i].pop_back();
  }
  adj[i].push_back(-1);
  return;
}

int loop(vector<bool> visited, vector<vector<int> > &adj, int index){
  
  // if node has been deleted then return
  if (adj[index].size() && adj[index][0] == -1){
    return 0;
  }

  // if this node has been visited then return 1
  if (visited[index] == true){
    return 1;
  }

  // if node is a sink then delete and return
  if (!adj[index].size()){
    del(adj, index);
    return 0;
  }

  // else mark this node visited and explore further
  visited[index] = true;
  for (int i=0; i<adj[index].size(); i++){
    int n = loop(visited, adj, adj[index][i]);
    if (n){
      return 1;
    }
  }

  return 0;
}

int acyclic(vector<vector<int> > &adj) {

  if (!adj.size()){
    return 0;
  }

  for (int i=0; i<adj.size(); i++){

    vector<bool> visited(adj.size(), false);
    int res = loop(visited, adj, i);
    if (res){
      return 1;
    }
  }
  return 0;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  std::cout << acyclic(adj);
}
