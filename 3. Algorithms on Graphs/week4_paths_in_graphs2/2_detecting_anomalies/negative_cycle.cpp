#include <iostream>
#include <vector>

using std::vector;
using std::cout;

int negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost) {

  // if invalid input return -1
  if (!adj.size() || !cost.size()){
    return -1;
  }

  // initalise helper data
  vector<long long> dist(adj.size(), 3372036854775807);
  dist[0] = 0;

// ---------- run bellman-ford algorithm
for (int loop=0; loop<adj.size()-1; loop++){

  // Check whether there was a change on the last iteration, if no change then break

  // loop each node
    for (int source=0; source<adj.size(); source++){

      // for each node check all edges for relaxation opportunity
      for (int i=0; i<adj[source].size(); i++){

        int dest = adj[source][i];
        long long weight = cost[source][i];

        // check and update edge relaxation
        if (dist[dest] > dist[source] + weight){
          dist[dest] = dist[source] + weight;
        }
      }
    }   
}

  // run an additional relaxation check on edges
  // if any edge is relaxed then there must be a negative cycle in the graph
  for (int i=0; i<adj.size(); i++){
    for (int j=0; j<adj[i].size(); j++){

      int dest = adj[i][j];
      int source = i;
      long long weight = cost[source][j];

      if (dist[dest] > dist[source] + weight){
        //cout<<"detected on: "<<source+1<<" -> "<<dest+1<<" with weight "<<weight<<"\n";
        //cout<<"dist["<<source+1<<"] = "<<dist[source]<<",  dist["<<dest+1<<"] = "<<dist[dest]<<"\n\n";
        return 1;
      }
      //cout<<"safe on: "<<source+1<<" -> "<<dest+1<<" with weight "<<weight<<"\n";
      //cout<<"dist["<<source+1<<"] = "<<dist[source]<<",  dist["<<dest+1<<"] = "<<dist[dest]<<"\n\n";
    }
  }

  return 0;
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
  std::cout << negative_cycle(adj, cost);
}
