#python3
import heapq
import sys

# overlap_graph class which creates a highly connected graph from list of reads. Connects nodes (reads) by their longest
# suffix/prefix match between two nodes. Fucnction to find hamiltonian paths to construct genome candidate.
class overlap_graph:

    def __init__(self, reads, k=12, error_prone=False, tests=False) -> None:
        self.reads = reads
        self.error_prone = error_prone
        self.candidate_pairs = self.__find_candidate_pairs(reads, k)
        self.overlaps = self.__find_overlaps()
        self.hamiltonian_path = []
        self.best_weight = 0
        self.tests = tests
        return
    
    # printing format for class including details of current state of best paths, candidate pairs, and overlaps
    def __str__(self):
        output = ''
        output += '--- OVERLAP GRAPH ---\n\n(candidate pair) - overlap\n'
        for key in self.candidate_pairs:

            output += f'{self.reads[key[0]], self.reads[key[1]]} '
            if key in self.overlaps:
                output += str(self.overlaps[key])
            output += '\n'

        output += '\nBest Path\n'
        for element in self.hamiltonian_path:
            output += str(element) +', '

        return output


    # private function to calculate the largest suffix/prefix overlap between to input reads
    def __compute_overlap(self, read1, read2):

        max_length = 0
        min_length = min(len(read1), len(read2))
        for i in range(1, min_length + 1):
            suffix = read1[-i:] # suffix equals last 'i' characters of read1
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
            overlaps[(i, j)] = overlap_size

        return overlaps

    # private function to return set of pairs of candidate read indexes from the input reads list
    def __find_candidate_pairs(self, reads, k):

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
        
        # begin the path at the first index of reads
        path = [self.reads[0]]
        visited = set()
        visited.add(self.reads[0])
        best_path = []
        pq = []

        # add start node to pq
        neighbours = [(start, end, self.overlaps[(start, end)]) for start, end in self.candidate_pairs if start == 0]
        for neighbour in neighbours:
            heapq.heappush(pq, (-neighbour[2], neighbour[1], path.copy(), visited.copy()))

        while pq:

            current_overlap, current_index, path, visited = heapq.heappop(pq)

            neighbours = [(start, end, self.overlaps[(start,end)]) for start, end in self.candidate_pairs if start == current_index and end not in path]
            neighbours = sorted(neighbours, key=lambda x: x[2])

            # check continue conditions
            if current_index in path or current_index in visited:
                continue

            # add current to path and visited
            path.append(current_index)
            visited.add(current_index)

            # add unvisited neighbouring nodes to the pq
            for neighbour in neighbours:
                heapq.heappush(pq, (current_overlap-neighbour[2], neighbour[1], path.copy(), visited.copy()))

            # check for path containing all indexes
            if len(visited) == len(self.reads):

                # add overlap from last index in current path back to first index
                total_overlap = current_overlap - self.overlaps.get((current_index, 0), 0)
                
                # if total overlap is the best found path through graph update best path / overlap member variables
                if total_overlap < self.best_weight:
                    self.best_weight = total_overlap
                    best_path = path
        
        return best_path

    # private function to assemble genome from the computed hamiiltonian path previously constructed
    def __assemble_genome(self):
        
        # for each index in best path, append non-overlap section to the genome
        candidate_genome = self.reads[0]
        previous_index = 0
        for index in self.hamiltonian_path[1:]:

            # get overlap from previous read index to current
            current_overlap = self.overlaps.get((previous_index, index), 0)

            # add non-overlapping section to candidate genome
            candidate_genome += self.reads[index][current_overlap:]

            previous_index = index

        # remove matching prefix / suffix from candidate genome since reads[0] appears at start and end of path
        candidate_genome = candidate_genome[:-self.overlaps.get((previous_index, 0), 0)]

        return candidate_genome

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
    graph = overlap_graph(reads, error_prone=False, k=12)
    graph.compute_candidate_genome()
    #print(graph)
    graph.print_genome()

    return

if __name__ == '__main__':
    main()
