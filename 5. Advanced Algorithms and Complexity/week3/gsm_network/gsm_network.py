# python3
n, m = map(int, input().split())
edges = [ list(map(int, input().split())) for i in range(m) ]

def printEquisatisfiableSatFormula():
    
    # number of clauses is 3 for every edge plus 1 for each vertex
    num_clauses = m*3 + n
    clauses = []

    # number of variables is number of colours times by number of vertexes
    num_variables = 3*n

    # for each vertex, add clause that one of the colours must be true
    for i in range(1, n+1):
        temp = []
        for j in range(1,4):
            temp.append((i-1)*3+j)
        clauses.append(temp)

    # add clauses for each edge in the graph
    for edge in edges:

        # initialise vertexes within this edge
        u, v = edge
        clauses.append([-((u-1)*3+1), -(((v-1)*3)+1)])
        clauses.append([-((u-1)*3+2), -(((v-1)*3)+2)])
        clauses.append([-((u-1)*3+3), -(((v-1)*3)+3)])
    
    print(len(clauses), num_variables)
    for clause in clauses:
        print(' '.join(map(str, clause)), '0')


printEquisatisfiableSatFormula()
