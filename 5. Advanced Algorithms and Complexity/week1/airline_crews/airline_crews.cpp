#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <queue>

using std::vector;
using std::cin;
using std::cout;
using std::queue;

class FlowGraph {
public:
    struct Edge {
        int from, to, capacity, flow;
    };

private:
    /* List of all - forward and backward - edges */
    vector<Edge> edges;

    /* These adjacency lists store only indices of edges in the edges list */
    vector<vector<size_t> > graph;

public:
    explicit FlowGraph(size_t n): graph(n) {}

    void add_edge(int from, int to, int capacity) {
        /* Note that we first append a forward edge and then a backward edge,
         * so all forward edges are stored at even indices (starting from 0),
         * whereas backward edges are stored at odd indices in the list edges */
        Edge forward_edge = {from, to, capacity, 0};
        Edge backward_edge = {to, from, 0, 0};
        graph[from].push_back(edges.size());
        edges.push_back(forward_edge);
        graph[to].push_back(edges.size());
        edges.push_back(backward_edge);
    }


    void print_edges(){
        cout<<"- EDGES -\n";
        for (int i=0; i<edges.size(); i++){
          if (true){
            cout<<i<<"-> from: "<<edges[i].from<<",  to: "<<edges[i].to<<", capacity: "<<edges[i].capacity<<", flow: "<<edges[i].flow<<"\n";
          }
        }
        cout<<"\n";
        return;
    }

    void print_ids(){
        return;
    }

    size_t size() const {
        return graph.size();
    }

    const vector<size_t>& get_ids(int from) const {
        return graph[from];
    }

    const Edge& get_edge(size_t id) const {
        return edges[id];
    }

    void add_flow(size_t id, int flow) {
        /* To get a backward edge for a true forward edge (i.e id is even), we should get id + 1
         * due to the described above scheme. On the other hand, when we have to get a "backward"
         * edge for a backward edge (i.e. get a forward edge for backward - id is odd), id - 1
         * should be taken.
         *
         * It turns out that id ^ 1 works for both cases. Think this through! */
        edges[id].flow += flow;
        edges[id ^ 1].flow -= flow;
    }
};

void bfs(FlowGraph &Gf, vector<int> &prev){

    // reset values for prev to recalculate path
    // PREV[i] stores the id of the edge to the previous node
    for (int i=0; i<prev.size(); i++){
        prev[i] = -1;
    }

    // create queue of vertexes to visit starting at 0
    queue<int> q;
    q.push(0);
    while (!q.empty()){

        int index = q.front();
        q.pop();
        vector<size_t> current = Gf.get_ids(index);
        //print(current, "EDGES OUT OF NODE 1");

        // for each node which is reachable from the current node
        for (int i=0; i<current.size(); i++){

            // check whether we can reach this node or if it has already been reached.
            FlowGraph::Edge path = Gf.get_edge(current[i]);
            //FlowGraph::Edge opp = Gf.get_edge(current[i]^1);
            int to = path.to;
            
            // if to has already been visited then don't add to the queue
            if (prev[to] != -1){
                continue;
            }

            // if the edge is fully saturated
            if (path.capacity <= path.flow){
                continue;
            }

            prev[to] = current[i];

            if (to == Gf.size()-1){
                return;
            }

            q.push(to);

        }


    }

}

void flow(FlowGraph &Gf){
          // iterate until no more flow can be added
    while (true){

        // find path to tap from node 1 to node graph.size();
        vector<int> prev(Gf.size(), -1);
        bfs(Gf, prev);

        //print(prev, "PREV");

        // if there is no path from node 1 to node graph.size() return current flow
        if (prev[Gf.size()-1] == -1){
            return;
        }

        // calculate minimum flow required and add to flow
        int to = Gf.size()-1;
        int minFlow = 999999;
        while (to != 0){

            // calculate which edge to look at
            int id = prev[to];
            to = Gf.get_edge(id).from;
            FlowGraph::Edge current = Gf.get_edge(id);

            // check for updating min conditions
            if (current.capacity - current.flow < minFlow){
                minFlow = current.capacity - current.flow;
            }

            // update index
            to = current.from;

        }

        // update graph flows
        to = Gf.size()-1;
        while (to != 0){
            
            // calculate the corresponding edge (backwards)
            int id = prev[to];
            to = Gf.get_edge(id).from;
            Gf.add_flow(id, minFlow);

        }
      }
    }

FlowGraph make_Gf(vector<vector<bool> > adj){

  size_t s = adj.size() + adj[0].size() + 2;
  FlowGraph Gf(s);

  // for each element in the adj matrix. If the given crew and flight are
  // compatible then create an edge between them
  for (int i=0; i<adj.size(); i++){
    for (int j=0; j<adj[0].size(); j++){

      if (adj[i][j] == true){
        Gf.add_edge(j+1, i+adj[0].size()+1, 1);
      }

    }
  }

  // add edges from source to flights and crews to sink
  for (int i=0; i<adj[0].size(); i++){
    Gf.add_edge(0,i+1,1);
  }
  for (int i=0; i<adj.size(); i++){
    Gf.add_edge(i+adj[0].size()+1, s-1, 1);
  }

  return Gf;
}

class MaxMatching {
 public:
  void Solve() {
    vector<vector<bool> > adj_matrix = ReadData();
    FlowGraph Gf = make_Gf(adj_matrix);
    flow(Gf);
    vector<int> matching = FindMatching(Gf, adj_matrix);
    WriteResponse(matching);
  }

 private:
  vector<vector<bool> > ReadData() {
    int num_left, num_right;
    cin >> num_left >> num_right;
    vector<vector<bool> > adj_matrix(num_left, vector<bool>(num_right));
    for (int i = 0; i < num_left; ++i)
      for (int j = 0; j < num_right; ++j) {
        int bit;
        cin >> bit;
        adj_matrix[i][j] = (bit == 1);
      }
    return adj_matrix;
  }

  void WriteResponse(const vector<int>& matching) {
    for (int i = 0; i < matching.size(); ++i) {
      if (i > 0)
        cout << " ";
      if (matching[i] == -1)
        cout << "-1";
      else
        cout << (matching[i] + 1);
    }
    cout << "\n";
  }

  vector<int> FindMatching(FlowGraph &Gf, vector<vector<bool> > &adj) {
    // Replace this code with an algorithm that finds the maximum
    // matching correctly in all cases.

    vector<int> res(adj.size(), -1);

    for (int i=0; i<adj.size(); i++){
      vector<size_t> t = Gf.get_ids(i+1+adj[0].size());
      for (int j=0; j<t.size(); j++){
        FlowGraph::Edge temp = Gf.get_edge(t[j]);
        if (temp.flow == -1){
          res[i] = temp.to - 1;
        }
      }
    }

  //Gf.print_edges();
  return res;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  MaxMatching max_matching;
  max_matching.Solve();
  return 0;
}
