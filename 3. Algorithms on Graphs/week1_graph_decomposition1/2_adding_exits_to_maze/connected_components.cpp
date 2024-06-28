#include <iostream>
#include <vector>

using std::vector;
using std::pair;

void mark(vector<vector<int> > &adj, int i){

  // if the node i doesn't have any neighbours or has already been marked then return
  if (!adj[i].size() || adj[i][adj[i].size()-1] == -1){
    return;
  }

  // mark the current node as visited. 
  adj[i].push_back(-1);

  // call mark for all neighbouring nodes.
  for (int j=0; j<adj[i].size()-1; j++){
    mark(adj, adj[i][j]);
  }

  return;
}

int number_of_components(vector<vector<int> > &adj) {
  int res = 0;

  // if the adj matrix is empty then return zero
  if (!adj.size()){
    return 0;
  }

  // iterate through each node and if its not been visited then add a component. 
  for (int i=0; i<adj.size(); i++){

    if (adj[i].size() && adj[i][adj[i].size()-1] == -1){
      continue;
    }

    // from the not visited node, mark all neighbouring nodes as visited. 
    mark(adj, i);

    // iterate total components
    res += 1;
  }

  return res;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << number_of_components(adj);
}
