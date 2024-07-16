#python3
import sys

# class to construct graph and solve for eulerian cycle within graph
class Eulerian_graph:

    def __init__(self, input=None):

        # if no input passed to constructor then get own input
        if not input:
            self.__get_input()

        return
    
    def print(self):
        for key, item in self.nodes.items():
            pass
            #print(f'{key}: {item}')
        return
    
    def __get_input(self):
        
        # first line defines number of verticies and edges
        verticies_count, edges_count = map(int, input().split())
        self.nodes = {node: [] for node in range(1, verticies_count+1)}
        self.reverse = {node: [] for node in range(1, verticies_count+1)}
        self.in_out_edges = {node: [0, 0] for node in range(1, verticies_count+1)}

        # for each edge, add to adjacency list for given source node
        for _ in range(edges_count):
            source, dest = map(int, input().split())
            self.nodes[source].append(dest)
            self.reverse[dest].append(source)
            self.in_out_edges[source][1] += 1
            self.in_out_edges[dest][0] += 1

        return
    
    def has_eulerian_cycle(self) -> bool:
        for node in self.in_out_edges:
            if self.in_out_edges[node][0] != self.in_out_edges[node][1]:
                return False
        return True
    
    def find_eulerian(self):
        # Hierholzer's algorithm to find the Eulerian cycle
        stack = []
        cycle = []
        current = next(iter(self.nodes))  # start from any node

        while stack or self.nodes[current]:
            if not self.nodes[current]:
                cycle.append(current)
                current = stack.pop()
            else:
                stack.append(current)
                next_node = self.nodes[current].pop()
                current = next_node

        cycle.append(current)
        self.eulerian_cycle = cycle[::-1]
        return
    
    def print_cycle(self) -> None:
        for node in self.eulerian_cycle[:-1]:
            print(node, end=' ')

def main():

    graph = Eulerian_graph()
    if graph.has_eulerian_cycle():
        print(1)
        graph.find_eulerian()
        graph.print_cycle()
    else:
        print(0)

    return 0

if __name__ == '__main__':
    main()