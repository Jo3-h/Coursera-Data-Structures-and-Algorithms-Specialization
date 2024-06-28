#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>

using std::vector;
using std::pair;
using std::cout;
using std::stack;

void del(vector<vector<int> > &rev, int i){
  
  // if node has zero neighbours then push -1 to adj list
  //cout<<"del: "<<i+1<<"\n";
  rev[i].push_back(-1);

}

void dfs(vector<vector<int> > &rev, stack<int> &order, int i){
  
  // if node has already been deleted then return
  if ((rev[i].size() && rev[i][rev[i].size()-1] == -1) || i==-1){
    return;
  }

  // if node is a sink then add to stack and delete node
  if (!rev[i].size()){

    order.push(i);
    del(rev, i);
    return;
  }

  del(rev, i);

  // if node is not a sink then add all neighbours
  for(int j=0; j<rev[i].size()-1; j++){
    dfs(rev, order, rev[i][j]);
  }

  // add this node to the stack and return
  order.push(i);
  return;

}

void getStack(vector<vector<int> > &rev, stack<int> &order){

  for (int i=0; i<rev.size(); i++){
    dfs(rev, order, i);
  }

}

void printStack(stack<int> order){

  cout<<"stack: ";
  while (!order.empty()){
    cout<<order.top()+1<<" ";
    order.pop();
  }
  cout<<"\n";
  return;
}

void explore(vector<vector<int> > &adj, int i, vector<int> &used){

  // if node has been explored or i is invalid
  if (i<0 || used[i] == 1){

    return;
  }

  // else if sink then
  if (!adj[i].size()){

    used[i] = 1;
    return;
  }

  used[i] = 1;
  for (int j=0; j<adj[i].size(); j++){

    explore(adj, adj[i][j], used);

  }

  return;
}

int number_of_strongly_connected_components(vector<vector<int> > adj, vector<vector<int> > rev) {
  int result = 0;
  
  // if adj is empty
  if (!adj.size()){
    return 0;
  }

  // set stack to be stack of post order elements. 
  stack<int> order;
  getStack(rev, order);
  //printStack(order);
  vector<int> used(order.size(), 0);

  while (order.size()){

    // explore the top of the stack
    explore(adj, order.top(), used);

    while (order.size() && used[order.top()] == 1){

      order.pop();
      if (!order.size()){
        break;
      }
    }
    //cout<<"\nsuccess";
    //increment result
    result += 1;

  }


  return result;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > rev(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    rev[y - 1].push_back(x - 1);
  }
  std::cout << number_of_strongly_connected_components(adj, rev);
}
