#include <iostream>
#include <vector>
#include <queue>
#include <string>

using std::queue;
using std::vector;
using std::cout;
using std::string;

/* This class implements a bit unusual scheme for storing edges of the graph,
 * in order to retrieve the backward edge for a given edge quickly. */
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
            cout<<i<<"-> from: "<<edges[i].from<<",  to: "<<edges[i].to<<", capacity: "<<edges[i].capacity<<"\n";
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

void print(vector<int> prev, string name){

    cout<<name<<"\n";
    for (int i=0; i<prev.size(); i++){
        cout<<i+1<<" -> "<<prev[i]<<"\n";
    }

}

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

FlowGraph read_data() {
    int vertex_count, edge_count;
    std::cin >> vertex_count >> edge_count;
    FlowGraph graph(vertex_count);
    for (int i = 0; i < edge_count; ++i) {
        int u, v, capacity;
        std::cin >> u >> v >> capacity;
        graph.add_edge(u - 1, v - 1, capacity);
    }
    return graph;
}

int max_flow(FlowGraph& Gf, int from, int to) {
    int flow = 0;

    //Gf.print_edges();
    
    // iterate until no more flow can be added
    while (true){

        // find path to tap from node 1 to node graph.size();
        vector<int> prev(Gf.size(), -1);
        bfs(Gf, prev);

        //print(prev, "PREV");

        // if there is no path from node 1 to node graph.size() return current flow
        if (prev[Gf.size()-1] == -1){
            return flow;
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
        flow += minFlow;

        // update graph flows
        to = Gf.size()-1;
        while (to != 0){
            
            // calculate the corresponding edge (backwards)
            int id = prev[to];
            to = Gf.get_edge(id).from;
            Gf.add_flow(id, minFlow);

        }
    }

    return flow;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    FlowGraph graph = read_data();

    std::cout << max_flow(graph, 0, graph.size() - 1) << "\n";
    return 0;
}
