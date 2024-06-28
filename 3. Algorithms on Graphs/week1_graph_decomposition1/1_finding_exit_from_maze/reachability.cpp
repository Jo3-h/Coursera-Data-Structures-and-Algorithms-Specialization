#include <iostream>
#include <vector>

using std::vector;
using std::pair;
using std::cout;

int reach(vector<vector<int> > &adj, int x, int y) {

  // check if node has been visited
  if (!(adj[x].size()) || adj[x][adj[x].size()-1] == -1){
    return 0;
  } 

  // mark node as searched
  adj[x].push_back(-1);

  // loop through each neighbour of start
  for (int i=0; i<adj[x].size()-1; i++){

  // check whether the neighbour is the dest
    if (adj[x][i] == y){
      return 1;
    } else {

      // if neighbour is not the dest then search that neighbours neighbours.
      int j = reach(adj, adj[x][i], y);

      // if reach ever returns 1 then recursively return 1
      if (j == 1){
        return 1;
      }
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
    adj[y - 1].push_back(x - 1);
  }
  int x, y;
  std::cin >> x >> y;
  std::cout << reach(adj, x - 1, y - 1);
  return 0;
}
