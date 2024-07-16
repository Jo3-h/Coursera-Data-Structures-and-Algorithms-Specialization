#python3
import sys

# class to store input of puzzle in correct format and hold methods to calculate a valid composition of puzzle pieces
class puzzle_assembly_graph:

    def __init__(self, pieces=None, piece_count=25):

        # initialise member variables
        dim = pow(piece_count, 0.5)
        if not dim.is_integer():
            print('Please use a square number of pieces')
            return
        self.dim = int(dim)
        self.result_puzzle = []
        for _ in range(self.dim):
            self.result_puzzle.append([None]*self.dim)
        self.used_pieces = {key: False for key in range(piece_count)}

        # check whether pieces were passed to init, if not collect from command line
        self.pieces = pieces
        if not pieces:
            self.pieces = self.__get_input(piece_count=piece_count)

        return
    
    def __str__(self):
        return 'print'
        #return ''.join(f'{i}: {piece} \n' for i, piece in enumerate(self.pieces))

    # private function to get input for pieces from the command line, called if no puzzle pieces are passed to init function
    def __get_input(self, piece_count=25):

        # initialise list of piece definitions, input size set at 25 for this problem
        pieces = []
        for i in range(piece_count):
            line = sys.stdin.readline().strip()
            piece = tuple(line[1:-1].split(','))
            pieces.append(piece)
        return pieces
    
    # private function to check whether a piece is vaild for a given position based on the surrounding pieces
    def __is_valid_position(self, piece, row, col):

        # check left edge of piece in (row, col), if it is left boundary then check for being black
        if col == 0 and piece[1] != 'black':    
            return False
        elif col > 0 and piece[1] != self.result_puzzle[row][col-1][3]:
            return False
        
        # check top edge of piece in (row, col), if it is top boundary then check for being black
        if row == 0 and piece[0] != 'black':
            return False
        elif row > 0 and piece[0] != self.result_puzzle[row-1][col][2]:
            return False
        
        # only need to check bottom and right sides for boundaries since at checking any position the positions to the right and below won't be filled yet
        if row == self.dim - 1 and piece[2] != 'black':
            return False
        
        if col == self.dim - 1 and piece[3] != 'black':
            return False    

        return True
    
    # function for external calling to solve the puzzle positions, recursively looks for correct pieces and utilised backtracking 
    # if a configuration will result in no possible solutions
    def solve(self, row, column):

        # if row equals value of dim then complete puzzle (due to 0 indexing of list)
        if row == self.dim:
            return True
        
        # calculate next position requiring filling
        next_row, next_column = (row, column + 1) if column + 1 < self.dim else (row+1, 0)

        # find a vaild un-used piece for the next location
        for i, piece in enumerate(self.pieces):
            if not self.used_pieces[i] and self.__is_valid_position(piece, row, column):
                self.used_pieces[i] = True
                self.result_puzzle[row][column] = piece
                if self.solve(next_row, next_column):
                    return True
                self.used_pieces[i] = False
                self.result_puzzle[row][column] = None
            
        # if method hasn't found valid solution from above loop then solution doesn't exist 
        return False
    
    def print_result(self):
        for row in self.result_puzzle:
            for j, piece in enumerate(row):
                print('('+piece[0]+','+piece[1]+','+piece[2]+','+piece[3]+')', end='')
                if j < self.dim - 1:
                    print(';', end='')
            #print()
    
    def format_output(self):
        for row in self.result_puzzle:
            print(";".join([str(t) for t in row]).replace(' ', '').replace("'", ""))

def main():

    puzzle = puzzle_assembly_graph(piece_count=25)
    if puzzle.solve(0,0):
        puzzle.format_output()
        #puzzle.print_result()

    return 0

if __name__ == '__main__':
    main()