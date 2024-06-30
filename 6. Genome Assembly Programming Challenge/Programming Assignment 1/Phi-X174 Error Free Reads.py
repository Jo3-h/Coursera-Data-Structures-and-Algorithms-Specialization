import heapq

def longest_substring(read1, read2):
    return 0

# overlap_graph class which creates a highly connected graph from list of reads. Connects nodes (reads) by their longest
# suffix/prefix match between two nodes. Fucnction to find hamiltonian paths to construct genome candidate.
class overlap_graph:

    def __init__(self, reads):
        self.reads = reads
        self.nodes = {}

        # for each read in the reads input, add a node and connect to all existing nodes
        # with directional link equal to the longest prefix/sufffix match from 1 -> 2
        for read in reads:

            # add read node to 
            self.add_node(read)


    def add_node(self, read):

        # if node is not already in nodes then add
        if read not in self.nodes.keys():
            self.nodes[read] = {}
        else:
            # node has been repeated
            for dest in self.nodes.keys():
                self.add_link(read, dest)

        return
    
    def add_link(self, source: str, dest: str) -> None:

        index = len(dest)
        link = 0
        # loop through values of start index until a vaild suffix/prefix match is found or start index equals length of source
        while index < len(source):
            if source[-index:] == dest[:index]:
                link = index
                break
            else:
                index -= 1
        
        if link > 0:
            if source not in self.nodes:
                self.nodes[source] = {}
            self.nodes[source][dest] = link

        return

    def find_hamiltonian(self):

        # create visited set to keep track of nodes already included in path
        visited = set()
        current_node = list(self.nodes.keys())[0]
        visited.add(current_node)
        path = [current_node]
        pq = []

        # add neighbours to the priority queue and negate link since pq will give smallest values first
        for neighbour, link in self.nodes[current_node].items():
            heapq.heappush(pq, (-link, current_node, neighbour))

        # while there are nodes in the queue still, investigate queued nodes
        while pq:
            
            link, current_node, dest = heapq.heappop(pq)
            if current_node in visited:
                continue
            
            visited.add(current_node)
            path.append(dest)

        return
    
    

def parse_input():
    reads = []
    for _ in range(1,1619):
        reads.append(str(input()))
    return reads

def main():

    # get input from the command line
    reads = parse_input

    # construct an overlap graph from reads
    graph = overlap_graph(reads)
    graph.find_hamiltonian()

    return

if __name__ == '__main__':
    main()