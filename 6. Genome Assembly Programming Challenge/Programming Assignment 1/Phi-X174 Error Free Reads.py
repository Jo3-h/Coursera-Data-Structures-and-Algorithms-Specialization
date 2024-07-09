#python3
import heapq
import sys

# overlap_graph class which creates a highly connected graph from list of reads. Connects nodes (reads) by their longest
# suffix/prefix match between two nodes. Fucnction to find hamiltonian paths to construct genome candidate.
class overlap_graph:

    def __init__(self, reads, error_prone=False, tests=False) -> None:
        self.reads = reads
        self.error_prone = error_prone
        self.candidate_pairs = self.__find_candidate_pairs(reads)
        self.overlaps = self.__find_overlaps()
        self.best_weight = 0
        self.tests = tests
        return

        # for each read in the reads input, add a node and connect to all existing nodes
        # with directional link equal to the longest prefix/sufffix match from 1 -> 2
        for read in reads:

            # add read node to 
            self.add_node(read)

    # private function to calculate the largest suffix/prefix overlap between to input reads
    def __compute_overlap(self, read1, read2):

        max_length = 0
        for i in range(1, len(read1)):
            suffix = read1[i:] # suffix equals last 'i' characters of read1
            prefix = read2[:i] # prefix equals first 'i' characters of read2

            # check whether suffix/prefix match, if new longest then update max_length
            if suffix == prefix:
                max_length = max(max_length, i)

        return max_length

    # private function to calculate overlaps of prefix/suffix between pairs of candidate reads
    def __find_overlaps(self):
        
        # for each candidate pair identified prior, 
        overlaps = {}
        for i, j in self.candidate_pairs:
            overlap_size = self.__compute_overlap(self.reads[i], self.reads[j])
            if overlap_size > 0:
                overlaps[(i, j)] = overlap_size

        return overlaps

    # private function to return set of pairs of candidate read indexes from the input reads list
    def __find_candidate_pairs(self, reads, k=12):

        # initialise k-mer dict
        kmer_dict = {}

        # iterate through each read in reads and add the index of that read to all k-mer dict entries of read
        for i, read in enumerate(reads):
            for j in range(len(read)+1-k):
                
                # kmer at this point is equal to substring of read from index j to j+k
                kmer = read[j:j+k]
                
                # if this is new kmer then add to kmer_dict before adding read index to kmer dict item
                if kmer not in kmer_dict:
                    kmer_dict[kmer] = []
                kmer_dict[kmer].append(i)
        
        # iterate back through reads, calculate kmers, identify candidate pairs of reads for potential suffix/prefix matches
        candidate_pairs = set()
        for i, read in enumerate(reads):
            for j in range(len(read)+1-k):

                # kmer at this point is equal to substring of read from index j to j+k
                kmer = read[j:j+k]

                for index in kmer_dict[kmer]:
                    if index != i:
                        candidate_pairs.add((i, index)) # add to candidate pairs the index of reads which have potential prefix/suffix match
        
        return candidate_pairs

    # private function to find hamiltonian path through graph
    def __find_hamiltonian_path(self):
        path = []
        visited = set()
        

    # private function to assemble genome from the computed hamiiltonian path previously constructed
    def __assemble_genome(self):
        genome = ''
        return genome

    def compute_candidate_genome(self):

        
        self.hamiltonian_path = self.__find_hamiltonian_path()
        self.candidate_genome = self.__assemble_genome()
        
        return

    def print_genome(self):
        print(self.candidate_genome)

def parse_input(test=False):
    if test:
        reads = []
        for _ in range(5):
            i = input().strip()
            reads.append(i)
        return reads
    return list(set(sys.stdin.read().strip().split()))

def main():

    # get input from the command line
    reads = parse_input(test=True)

    # construct an overlap graph from reads
    graph = overlap_graph(reads, error_prone=False)
    graph.compute_candidate_genome()
    graph.print_genome()

    return

if __name__ == '__main__':
    main()

'''
    def add_node(self, read):

        # if node is not already in nodes then add
        if read not in self.nodes.keys():
            self.nodes[read] = {}
            for dest in self.reads:
                if dest == read:
                    continue
                self.add_link(read, dest)

        return
    
    def add_link(self, source: str, dest: str) -> None:

        index = len(dest)
        link = 0
        # loop through values of start index until a vaild suffix/prefix match is found or start index equals length of source
        while index > 0:
            if source[-index:] == dest[:index]:
                link = index
                break
            else:
                index -= 1
        
        if link >= 0:
            if source not in self.nodes:
                self.nodes[source] = {}
            self.nodes[source][dest] = link

        return

    def find_hamiltonian(self):

        # create visited set to keep track of nodes already included in path
        visited = set()
        start_node = list(self.nodes.keys())[0]
        current_node = str(start_node)
        visited.add(current_node)
        path = [current_node]
        pq = []

        # add neighbours to the priority queue and negate link since pq will give smallest values first
        for neighbour, link in self.nodes[current_node].items():
            heapq.heappush(pq, (-link, current_node, neighbour, visited, path))

        # while there are nodes in the queue still, investigate queued nodes
        while pq:

            if self.tests:
                for item in pq:
                    print(item)
                print(20*'-', end='\n\n')
            
            current_cost, current_node, dest, visited, path = heapq.heappop(pq)

            if dest in visited:
                continue
            
            visited.add(dest)
            path.append(dest)

            for neighbour, link in self.nodes[dest].items():
                if neighbour not in visited:
                    heapq.heappush(pq, (current_cost-link, dest, neighbour, visited.copy(), path.copy()))

            # check whether all nodes have been visited, if so, add link from end node back to start node
            if len(self.nodes) == len(visited):
                total_weight = current_cost-self.nodes[dest][start_node]
                if total_weight < self.best_weight:
                    self.best_weight = total_weight
                    path.append(start_node)
                    self.best_path = path
        
        self.candidate_genome = self.compress(self.best_path, start_node)
        return
    
    # function to recompress reads on hamiltonian path to a genome candidate
    def compress(self, path, start_node):

        # if path is empty return
        if len(path) == 0:
            return False

        genome = path[0]
        for i in range(1, len(path)):
            current_read = path[i]
            prev_read = path[i-1]
            overlap_size = self.nodes[prev_read][current_read]
            genome += current_read[overlap_size:]

        return genome[:-len(start_node)]
'''