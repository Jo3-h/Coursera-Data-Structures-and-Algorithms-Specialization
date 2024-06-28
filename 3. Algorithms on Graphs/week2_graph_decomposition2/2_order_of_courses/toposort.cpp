#include <iostream>
#include <algorithm>
#include <vector>

using std::vector;
using std::pair;

vector<int> reverse(vector<int> order){

  vector<int> res;
  for (int i=order.size()-1; i>=0; i--){
    res.push_back(order[i]);
  }
  return res;
}

void del(vector<vector<int> > &adj, int i){
  while (adj[i].size()){
    adj[i].pop_back();
  }
  adj[i].push_back(-1);
}

void dfs(vector<vector<int> > &adj, vector<int> &used, vector<int> &order, int x) {

  // if node has been deleted then return
  if (used[x]){
    return;
  }

  // if node is a sink then add to back of order and remove
  if (!adj[x].size()){
    used[x] = 1;
    order.push_back(x);
    del(adj, x);
    return;
  }

  // if node hasn't been used, add its neighbours to the order. 
  for (int i=0; i<adj[x].size(); i++){
    dfs(adj, used, order, adj[x][i]);
  }

  used[x] = 1;
  order.push_back(x);
  return;

}     

vector<int> toposort(vector<vector<int> > adj) {
  vector<int> used(adj.size(), 0);
  vector<int> order;

  // if graph is empty then return
  if (!adj.size()){
    return order;
  }

  // start at first node
  for (int i=0; i<adj.size(); i++){
    dfs(adj, used, order, i);
  }

  // reverse order
  order = reverse(order);

  return order;
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
  vector<int> order = toposort(adj);
  for (size_t i = 0; i < order.size(); i++) {
    std::cout << order[i] + 1 << " ";
  }
}
