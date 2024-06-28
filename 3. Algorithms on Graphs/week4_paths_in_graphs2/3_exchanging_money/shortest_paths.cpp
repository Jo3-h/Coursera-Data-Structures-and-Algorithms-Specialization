#include <iostream>
#include <limits>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;
using std::cout;

void bfs2(vector<vector<int> > &adj, int s, vector<int> &reachable){

  queue<int> q;
  q.push(s);

  while (!q.empty()){

    int index = q.front();
    q.pop();

    if (reachable[index]){
      continue;
    }

    for (int i=0; i<adj[index].size(); i++){
      q.push(adj[index][i]);
    }

    reachable[index] = 1;

  }


}

void bfs(vector<vector<int> > &adj, queue<int> q, vector<int> &shortest){

  while (!q.empty()){

    // pop the top index of the queue
    int index = q.front();
    q.pop();

    // if index has already been searched then return
    if (!shortest[index]){
      continue;
    }

    // if index hasn't been searched then add all neighbours to queue
    for (int i=0; i<adj[index].size(); i++){
      q.push(adj[index][i]);
    }

    // set shortest at this index to be zero
    shortest[index] = 0;

  }

}

void shortest_paths(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, vector<long long> &distance, vector<int> &reachable, vector<int> &shortest) {

  // run reachable on adj to tell which nodes are reachable from s
  bfs2(adj, s, reachable);

  // now run bell-man ford on nodes using queue implementation to start from 
  // source node while also ignoring unreachable nodes
  distance[s] = 0;
  vector<bool> visited(adj.size(), false);
  queue<int> negcycle;
  queue<int> q;
  for (int loop=0; loop<adj.size(); loop++){

    // empty and reset queue
    while (!q.empty()){
      q.pop();
    }
    q.push(s);
    for (int i=0; i<visited.size(); i++){
      visited[i] = false;
    }

    while (!q.empty()){

      int index = q.front();
      q.pop();

      for (int i=0; i<adj[index].size(); i++){

        int dest = adj[index][i];
        long long weight = cost[index][i];

        //check relaxation conditions
        if (loop == adj.size()-1 && distance[dest] > distance[index] + weight){
          negcycle.push(dest);
        } else if (distance[dest] > distance[index] + weight){
          distance[dest] = distance[index] + weight;
        }

        // if next node has already been visited then move to next
        if (visited[dest] == true){
          continue;
        }

        // otherwise add to queue
        q.push(dest);

      }

      visited[index] = true;

    }

  }

  // now we can search for all nodes touchable from queue neg cycle and store in shortest
  bfs(adj, negcycle, shortest);

  // rest distances
  for (int i=0; i<distance.size(); i++){
    distance[i] = std::numeric_limits<long long>::max();
    visited[i] = false;
  }
  distance[s] = 0;

  // run bellman-ford again ignoring unreachable nodes and 
  for (int i=0; i<adj.size()-1; i++){

    while (!q.empty()){
      q.pop();
    }
    q.push(s);
    for (int j=0; j<visited.size(); j++){
      visited[j] = false;
    }

    while (!q.empty()){

      int source = q.front();
      q.pop();

      // if source is a negative cycle then skip
      if (shortest[source] == 0){
        continue;
      }

      for (int j=0; j<adj[source].size(); j++){

          int dest = adj[source][j];
          int weight = cost[source][j];

          if (distance[dest] > distance[source] + weight){
            distance[dest] = distance[source] + weight;
          }

          if (visited[dest] == true){
            continue;
          }

          q.push(dest);
      }
      visited[source] = true;
    }
  }

  return;
}


/*


  // change value of source node
  distance[s] = 0;

  // implement bellman-ford's algorithm 
  for (int i=0; i<adj.size()-1; i++){

    // loop through all nodes in graph
    for (int j=0; j<adj.size(); j++){

      // set the source node to be the first node explored
      int source;
      if (s+j >= adj.size()){
        source = s + j - adj.size();
      } else {
        source = s + j;
      }

      // search all neighbours and check for relaxing conditions
      for (int k=0; k<adj[source].size(); k++){

        int dest = adj[source][k];
        long long weight = cost[source][k];

        if (distance[dest] > distance[source] + weight){
          distance[dest] = distance[source] + weight;
        }
      }
    }
  }

  // intialise queue of nodes on negative cycles
  queue<int> q;

  // check all verticies again and create a queue of all nodes relaxed
  for (int i=0; i<adj.size(); i++){

    int source;
    if (i+s >= adj.size()){
      source = i + s - adj.size();
    } else {
      source = i + s;
    }

    // loop all neighbours and check for relaxing
    for (int j=0; j<adj[source].size(); j++){

      int dest = adj[source][j];
      long long weight = cost[source][j];

      if (distance[dest] > distance[source] + weight){
        q.push(source);
      }
    }
  }

  // run BFT on all nodes in queue to return all nodes which have -INF distance
  bfs(adj, q, shortest);

  // 
  bfs2(adj, s, reachable);

  // recalculate all the distances incase they have been affected by negative loops
  for (int i=0; i<distance.size(); i++){
    distance[i] = std::numeric_limits<long long>::max();
  }
  distance[s] = 0;

  // run bellman-ford 
//  cout<<"-------------------------------- calculating distances\n\n";
  for (int i=0; i<adj.size()-1; i++){
    
  //  cout<<"\n---------------------- iteration "<<i+1<<"\n\n";
    // loop each node starting at s
    for (int j=0; j<adj.size(); j++){

      int source = j+s;
      if (j + s >= adj.size()){
        source -= adj.size();
      }

    //  cout<<"-- consider source node "<<source+1<<"\n";
      if (!reachable[source] || !shortest[source]){
        continue;
      }
    //  cout<<"       node is being considered\n";
      for (int k=0; k<adj[source].size(); k++){
        
        int dest = adj[source][k];
        long long weight = cost[source][k];
      //  cout<<"              -> "<<dest+1<<" ("<<weight<<")";
        if (distance[dest] > distance[source] + weight){
      //    cout<<" - update\n";
          distance[dest] = distance[source] + weight;
        }
      //  cout<<"\n";
      }
    }
  }

  return;

}
*/

int main() {
  int n, m, s;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cin >> s;
  s--;
  vector<long long> distance(n, std::numeric_limits<long long>::max());
  vector<int> reachable(n, 0);
  vector<int> shortest(n, 1);
  shortest_paths(adj, cost, s, distance, reachable, shortest);

  for (int i = 0; i < n; i++) {
    if (!reachable[i]) {
      std::cout << "*\n";
    } else if (!shortest[i]) {
      std::cout << "-\n";
    } else {
      std::cout << distance[i] << "\n";
    }
  }
}
