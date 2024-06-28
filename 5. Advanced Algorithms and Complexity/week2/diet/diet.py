# python3
from sys import stdin
from itertools import combinations
import copy

class Equation:
  def __init__(self, a, b):
    self.a = a
    self.b = b

class Position:
  def __init__(self, column, row):
    self.column = column
    self.row = row

class linear_systems:

  def __init__(self, coefficients, solutions):

    self.coefficients = coefficients
    self.solutions = solutions
    self.rows = len(coefficients)
    self.columns = len(coefficients[0])

  def mark_pivot_element_used(self, pivot_element):
    self.used_rows[pivot_element.row] = True
    self.used_columns[pivot_element.column] = True

  def select_pivot_element(self):

    pivot = Position(0,0)
    while self.used_rows[pivot.row]:
      pivot.row += 1
    pivot.column = pivot.row
    while pivot.column < len(self.coefficients[pivot.row]) and self.coefficients[pivot.row][pivot.column] == 0:
      pivot.column += 1

    if pivot.column == len(self.coefficients[pivot.row]):
      return False
    else:
      return pivot
  
  def swap_lines(self, pivot_element):

    if pivot_element.row == pivot_element.column:
      return pivot_element

    temp_row = self.coefficients[pivot_element.row]
    temp_sol = self.solutions[pivot_element.row]

    self.coefficients[pivot_element.row] = self.coefficients[pivot_element.column]
    self.solutions[pivot_element.row] = self.solutions[pivot_element.column]

    self.coefficients[pivot_element.column] = temp_row
    self.solutions[pivot_element.column] = temp_sol

    # switch the used rows values 
    temp_flag = self.used_rows[pivot_element.row]
    self.used_rows[pivot_element.row] = self.used_rows[pivot_element.column]
    self.used_rows[pivot_element.column] = temp_flag

    pivot_element.row = pivot_element.column

    return pivot_element
  
  def process_pivot_element(self, pivot_element):

    # for this row, divide through by the coefficient of the pivot element
    mult = self.coefficients[pivot_element.row][pivot_element.column]
    for i in range(len(self.coefficients[pivot_element.row])):
      self.coefficients[pivot_element.row][i] = self.coefficients[pivot_element.row][i] / mult
    self.solutions[pivot_element.row] = self.solutions[pivot_element.row] / mult

    # take multiples of this row from all other rows to make pivot column
    for index, row in enumerate(self.coefficients):

      # if pivot row continue
      if index == pivot_element.row:
        continue

      # else take the value of this column in the current row and remove that many multiples of the pivot row
      mult = row[pivot_element.column]
      for j in range(len(row)):
        self.coefficients[index][j] = self.coefficients[index][j] - (mult * self.coefficients[pivot_element.row][j])
      self.solutions[index] = self.solutions[index] - (mult * self.solutions[pivot_element.row])

    return
  
  '''def print_coef(self, num):
    for i in range(len(self.coefficients)):
      print(' '*num+f'{self.coefficients[i]} <= {self.solutions[i]}')
    print('')

  def print_pivot(self, pivot_element):

    try:
      print(f'   ({pivot_element.row}, {pivot_element.column})')
    except:
      pass'''

  def solve_equations(self):

    self.used_rows = [False] * self.rows
    self.used_columns = [False] * self.columns

    #print('---')
    #self.print_coef(0)
    
    # gaussian elimination
    for i in range(self.rows):
      pivot_element = self.select_pivot_element()
      #self.print_pivot(pivot_element)
      #self.print_coef(3)
      if not pivot_element:
        return False
      pivot_element = self.swap_lines(pivot_element)
      self.process_pivot_element(pivot_element)
      self.mark_pivot_element_used(pivot_element)
      #self.print_coef(5)

    # return the solutions after gaussian
    return self.solutions

# take input from command line
num_restrictions, num_dishes = list(map(int, stdin.readline().split()))
coeff = []
for i in range(num_restrictions):
  coeff += [list(map(int, stdin.readline().split()))]
solu = list(map(int, stdin.readline().split()))
object = list(map(int, stdin.readline().split()))

# add constraints for amount values being >= 0 and effecitve infinity constraint
for i in range(num_dishes):
  temp = [0] * i
  temp.append(-1)
  for j in range(num_dishes-1-i):
    temp.append(0)
  coeff.append(list(temp))
  solu.append(0)

temp = [1] * num_dishes
coeff.append(list(temp))
solu.append(1000000000)

# iterate through subsets of all contraints of length equal to num_dishes to find vertex which satisies all constraints and maximises objective function
numbers = list(range(len(coeff)))
subsets = combinations(numbers, num_dishes)
'''print('FULL')
for i in range(len(coeff)):
  print(f'{coeff[i]} <= {solu[i]}')'''
current_best = -1000000000
vertex_conditions = []
current_result = []
test = True

for case in subsets:

  # create new coeff and solution matrix
  curr_coeff = []
  curr_solu = []
  for index in case:
    curr_coeff.append(copy.copy(coeff[index]))
    curr_solu.append(copy.copy(solu[index]))

  # solve system as equalities to get a vertex
  systems = linear_systems(curr_coeff, curr_solu)
  result = systems.solve_equations()   
  if not result:
    continue

  # ensure vertex is a valid solution
  valid = True
  for i, constraint in enumerate(coeff):
    
    left_hand_side = 0
    for index, element in enumerate(constraint):
      left_hand_side += element*result[index]

    if left_hand_side > solu[i] + 1e-3:
      valid = False
      break

  # check whether solution is larger than current max value of objective function found
  objective_value = 0
  if valid:
    
    # calculate objective value
    for i, value in enumerate(object):
      objective_value += value*result[i]

    # test if this is current best solution
    if objective_value > current_best:
      current_result = result
      current_best = objective_value
      vertex_conditions = case

  '''if test:
    print('')
    for i in range(len(result)-1):
      print(f'({result[i]})x({object[i]})', end=' + ')
    print(f'({result[len(result)-1]})x({object[len(result)-1]}) = {objective_value}')
    print(f'\nvalid: {valid}')
    print(f'result: {result}')
    print(f'curr best: {current_best}')
    print(f'curr resu: {current_result}')
      
print(f'vertex conditions: {vertex_conditions}')'''

if current_best == -1000000000:
  print("No solution")
elif (len(coeff) - 1) in vertex_conditions:
  print("Infinity")
else:  
  print("Bounded solution")
  print(' '.join(list(map(lambda x : '%.18f' % x, current_result))))
