#python3
import sys
from collections import defaultdict

# aux functions
def generate_kmers(n):
    kmers = []
    for i in range(2**n):
        kmer = bin(i)[2:].zfill(n)
        kmers.append(kmer)
    return kmers

# class for building de-bruijn graph and finding a eulerian path within
class universal_string_graph:

    def __init__(self, k=None):

        # if no input is given then get input from command line
        self.k = k
        self.nodes = set()
        prefix_suffix_count = defaultdict(int)
        self.graph = defaultdict(list)
        if not self.k:
            self.k = self.__get_input()

        # build de-bruijn graph
        for kmer in generate_kmers(self.k):
            prefix = kmer[:-1]
            suffix = kmer[1:]
            self.graph[prefix].append(suffix)
            self.nodes.add(prefix)
            self.nodes.add(suffix)
            prefix_suffix_count[prefix] += 1
            prefix_suffix_count[suffix] -= 1

        return
    
    def find_eulerian_path(self):
        def eulerian_path_hierholzer(graph, start):
            stack = [start]
            path = []

            while stack:
                current = stack[-1]
                if graph[current]:
                    next_node = graph[current].pop()
                    stack.append(next_node)
                else:
                    path.append(stack.pop())

            return path[::-1]

        # Find the Eulerian path starting from the identified start node
        start_node = bin(0)[2:].zfill(self.k-1)
        eulerian_path = eulerian_path_hierholzer(self.graph, start_node)

        # Convert path to circular string (remove duplicate overlap in the path)
        circular_string = str(eulerian_path[0]) + ''.join([str(node)[-1] for node in eulerian_path[1:]])

        return circular_string

    # private function to get input of k from command line
    def __get_input(self):
        return int(input())
    
    # public function to test values
    def test_print(self):
        '''
        print(f'k: {self.k}')
        for node in self.graph:
            print(f'{node}: {self.graph[node]}')
        '''
        return

def main():
    
    graph = universal_string_graph()
    result = graph.find_eulerian_path()
    print(result)

    return

if __name__ == '__main__':
    main()