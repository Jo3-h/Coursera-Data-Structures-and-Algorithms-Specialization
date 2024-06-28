# python3
import copy
rooms, corridors = map(int, input().split())
edges = [ list(map(int, input().split())) for i in range(corridors) ]

# function to solve for contraints
def solve_appartment():

    # variables is number of rooms multiplied by potential positions on the path
    num_variables = rooms*rooms
    clauses = []
    edges_matrix = [[False] * rooms for _ in range(rooms)]

    # create edges matrix
    for edge in edges:
        edges_matrix[edge[0]-1][edge[1]-1] = True
        edges_matrix[edge[1]-1][edge[0]-1] = True
    
    # create a matrix of numbers representing the index of positions
    graph = []
    pos = 1
    for i in range(rooms):
        next = []
        for j in range(rooms):
            next.append(pos)
            pos += 1
        graph.append(copy.copy(next))

    # ----- for each of the contraint types add constraints
    
    # Each vertex belongs to a path -> each row in graph has at least one true value
    for i in range(rooms):
        temp = []
        for j in range(rooms):
            temp.append(graph[i][j])
        clauses.append(copy.copy(temp))

    # Each vertex appears just once in a path
    for i in range(rooms):
        for j in range(rooms):
            for k in range(j + 1, rooms):
                clauses.append([-graph[i][j], -graph[i][k]])

    # Each position in a path is occupied
    for i in range(rooms):
        temp = []
        for j in range(rooms):
            temp.append(graph[j][i])
        clauses.append(copy.copy(temp))
            
    # no two verticies occupy the same position
    for i in range(rooms):
        for j in range(rooms):
            for k in range(j+1, rooms):
                clauses.append([-graph[j][i], -graph[k][i]])

    # two sucessive verticies must be joined by an edge
    for i in range(rooms):
        for j in range(rooms):

            # for every combination of vertexes, check if there is an edge between them
            if i != j and not edges_matrix[i][j]:
                for k in range(rooms-1):
                    clauses.append([-graph[i][k], -graph[j][k+1]])

    # print the results
    print(len(clauses), num_variables)
    for clause in clauses:
        print(' '.join(map(str, clause)), '0')


solve_appartment()