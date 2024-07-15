#python3
import heapq
import sys

class suffix_array:

    def __init__(self, text):
        self.text = text + '$'
        self.suffix_array, self.suffixes = self.__build_suffix_array()
        self.bwt = self.__build_bwt()

    def __str__(self):
        output = ''
        #output += f'text: {self.text}\n'
        #output += f'suffix array: {self.suffix_array}\n'
        #output += f'suffixes:\n'
        #for i, suffix in enumerate(self.suffixes):
        #    output += f'{i}: {suffix}\n'
        #output += f'bwt: {self.bwt}'
        return output

    def __build_suffix_array(self):
        suffixes = [(self.text[i:], i) for i in range(len(self.text))]
        suffixes.sort()
        return [suffix[1] for suffix in suffixes], suffixes

    def __build_bwt(self):
        return ''.join(self.text[i-1] for i in self.suffix_array)

class overlap_graph:

    def __init__(self, reads, k=12, error_prone=False, tests=False):
        self.reads = reads[:]
        self.error_prone = error_prone
        #self.concatenated_reads = '$'.join(reads) + '$'
        #self.suffix_array = suffix_array(self.concatenated_reads)
        #self.bwt = self.suffix_array.bwt
        self.candidate_pairs = self.__find_candidate_pairs(k)
        self.overlaps = self.__find_overlaps()
        self.hamiltonian_path = []
        self.best_weight = 0
        self.candidate_genome = None
        self.tests = tests

    def __str__(self):
        output = '--- OVERLAP GRAPH ---\n\n(candidate pair) - overlap\n'
        #for key in self.candidate_pairs:
        #    output += f'({self.reads[key[0]]}, {self.reads[key[1]]}) - {self.overlaps.get(key, 0)}\n'
        output += '\nBest Path: ' + ', '.join(map(str, self.hamiltonian_path)) + '\n'
        #output += f'Candidate Genome: {self.candidate_genome}'
        return output

    def find_longest_overlap(self, read1, read2):
        max_length = 0
        min_length = min(len(read1), len(read2))
        for i in range(1, min_length + 1):
            suffix = read1[-i:]
            prefix = read2[:i]
            if suffix == prefix:
                max_length = i
        return max_length

    def __find_overlaps(self):
        overlaps = {}
        for i, j in self.candidate_pairs:
            overlap_size = self.find_longest_overlap(self.reads[i], self.reads[j])
            overlaps[(i, j)] = overlap_size
        return overlaps

    def __find_candidate_pairs(self, k):
        kmer_dict = {}
        for i, read in enumerate(self.reads):
            for j in range(len(read) + 1 - k):
                kmer = read[j:j + k]
                if kmer not in kmer_dict:
                    kmer_dict[kmer] = []
                kmer_dict[kmer].append(i)
        candidate_pairs = set()
        for i, read in enumerate(self.reads):
            for j in range(len(read) + 1 - k):
                kmer = read[j:j + k]
                for index in kmer_dict.get(kmer, []):
                    if index != i:
                        candidate_pairs.add((i, index))
        return candidate_pairs

    def __find_hamiltonian_path_deep(self):
        path = [0]
        visited = set(path)
        best_path = []

        def dfs(current_index, current_path, current_visited):
            nonlocal best_path
            if len(current_path) == len(self.reads):
                total_overlap = sum(self.overlaps.get((current_path[i-1], current_path[i]), 0) for i in range(1, len(current_path)))
                if total_overlap < self.best_weight:
                    self.best_weight = total_overlap
                    best_path = current_path[:]
                return
            for neighbor in [j for i, j in self.candidate_pairs if i == current_index and j not in current_visited]:
                current_path.append(neighbor)
                current_visited.add(neighbor)
                dfs(neighbor, current_path, current_visited)
                current_path.pop()
                current_visited.remove(neighbor)

        dfs(0, path, visited)
        best_path.append(0)
        return best_path

    def __find_hamiltonian_path_greedy(self, start=0):
        path = [start]
        visited = set(path)
        current_index = start
        current_weight = 0
        total_weight = 0
        while len(path) < len(self.reads):
            current_weight, current_index = max((self.overlaps.get((current_index, j), 0), j) for i, j in self.candidate_pairs if i == current_index and j not in visited)
            total_weight += current_weight
            path.append(current_index)
            visited.add(current_index)
        path.append(start)
        return path, total_weight

    def assemble_genome(self, start=0):
        genome = self.reads[self.hamiltonian_path[0]]
        for i in range(1, len(self.hamiltonian_path)-1):
            overlap = self.overlaps.get((self.hamiltonian_path[i-1], self.hamiltonian_path[i]), 0)
            genome += self.reads[self.hamiltonian_path[i]][overlap:]
        overlap = self.overlaps.get((self.hamiltonian_path[-2], start), 0)
        if overlap == 0:
            return genome
        else:
            return genome[:-overlap]

    def compute_candidate_genome(self):
        temp_path, weight = self.__find_hamiltonian_path_greedy()
        if weight > self.best_weight:
            self.best_weight = weight
            self.hamiltonian_path = temp_path
        self.candidate_genome = self.assemble_genome(start=self.hamiltonian_path[0])

    def print_genome(self):
        print(self.candidate_genome)
        #print(f'Path: {self.hamiltonian_path}')

def parse_input(test=False):
    if test:
        reads = []
        for _ in range(5):
            i = input().strip()
            reads.append(i)
        return reads
    return list(set(sys.stdin.read().strip().split()))

def main():

    reads = parse_input(test=False)
    graph = overlap_graph(reads, k=12, error_prone=False)
    graph.compute_candidate_genome()
    graph.print_genome()

if __name__ == '__main__':
    main()
