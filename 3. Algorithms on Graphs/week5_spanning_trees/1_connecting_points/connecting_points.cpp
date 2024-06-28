#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <queue>

using std::vector;
using std::pair;
using std::priority_queue;

int find(int index, vector<int> parent){
  while (parent[index] != index){
    index = parent[index];
  }
  return index;
}

  void merge(int first, int second, vector<int> &parent, vector<int> &rank){

    int i = find(first, parent);
    int j = find(second, parent);

    // if finds are equivalent then do nothing
    if (i == j){
      return;
    }

    // if i is the taller tree
    if (rank[i] > rank[j]){
      parent[j] = i;
    } else {
      parent[i] = j;
      if (rank[i] == rank[j]){
        rank[j] = rank[j] + 1;
      }
    }

  return;

  }



double minimum_distance(vector<int> x, vector<int> y) {
  double result = 0.;

  priority_queue<pair<double, pair<int, int> > > q;

  // add all possible edged to a priority queue sorted by their length
  for (int i=0; i<x.size(); i++){
    for (int j=i; j<y.size(); j++){

      // if we are comparing a node with itself, continue
      if (i == j){
        continue;
      }

      pair<double, pair<int, int> > n;
      n.first = (-1)*(sqrt(pow(x[i]-x[j],2)+pow(y[i]-y[j],2)));
      n.second.first = i;
      n.second.second = j;
      q.push(n);

    }
  }

  // now add min of priority queue to res until all nodes are connected
  vector<int> parent(x.size());
  vector<int> rank(x.size());
  for (int i=0; i<x.size(); i++){
    parent[i] = i;
    rank[i] = 1;
  }

  while (!q.empty()){

    pair<double, pair<int, int> > cur = q.top();
    q.pop();

    // if nodes are in same set then continue
    if (find(cur.second.first, parent) == find(cur.second.second, parent)){
      continue;
    }

    // union these two nodes
    merge(cur.second.first, cur.second.second, parent, rank);

    // if at min one node is not conneced then connect both
    result += cur.first*(-1);
    merge(cur.second.first, cur.second.second, parent, rank);

    //std::cout<<"connected: "<<cur.second.first+1<<" <-> "<<cur.second.second+1<<"\n";

  }

  return result;
} 

int main() {
  size_t n;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;
}
