#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <cmath>
#include <queue> 

using std::vector;
using std::pair;
using std::priority_queue;
using std::make_pair;
using std::cout;

int find(int index, vector<int> parent){

  while (parent[index] != index){
    index = parent[index];
  }

  return index;

}

void merge(int first, int second, vector<int> &parent, vector<int> &rank){

  int i = find(first, parent);
  int j = find(second, parent);

  // if i and j are equal then the elements are already in the same set and we wont be joining them
  if (i == j){
    return;
  }

  // check which of i and j have the bigger rank to decide which should be the root
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

double clustering(vector<int> x, vector<int> y, int k) {

  // create a peiority queue of all potential edges
  priority_queue<pair<double, pair<int, int> > > pq;
  for (int i=0; i<x.size(); i++){
    for (int j=i; j<y.size(); j++){

      // if node is being compared to itself then return 
      if (i == j){
        continue;
      }

      // otherwise add the potential edge to the group
      double dist = (-1)*sqrt(pow(x[i]-x[j], 2)+pow(y[i]-y[j], 2));
      pq.push(make_pair(dist, make_pair(i, j)));
      //cout<<"pair made ("<<i<<", "<<j<<")\n";

    }
  }
  //cout<<"created queue\n";

  // set up disjoint sets data structure
  vector<int> parent(x.size());
  vector<int> rank(x.size());
  int sets = x.size();
  for (int i=0; i<x.size(); i++){
    parent[i] = i;
    rank[i] = 1;
  }
  

  // now empty the queue until there are 'k' separate disjoint sets
  while (sets > k && !pq.empty()){

    pair<double, pair<int, int> > curr = pq.top();
    pq.pop();

    // check whether they are part of the same set
    if (find(curr.second.first, parent) == find(curr.second.second, parent)){
      continue;
    }

    // make the connection and decrement the amount of sets in the graph
    sets = sets - 1;
    merge(curr.second.first, curr.second.second, parent, rank);
    //cout<<"connected: ("<<curr.second.first+1<<", "<<curr.second.second+1<<")\n";

  }

  // if all nodes are now in this set then return zero
  if (pq.empty()){
    return 0;
  }

  // search for the next instance in which the node that will be connected are in different clusters
  while (!pq.empty()){

    pair<double, pair<int, int> > current = pq.top();
    if (find(current.second.first, parent) == find(current.second.second, parent)){
      pq.pop();
      continue;
    }
    return (-1)*current.first;

  }

  return -1;

} 

int main() {
  size_t n;
  int k;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cin >> k;
  std::cout << std::setprecision(10) << clustering(x, y, k) << std::endl;
}
