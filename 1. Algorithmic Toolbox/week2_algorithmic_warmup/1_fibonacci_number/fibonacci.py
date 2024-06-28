# Uses python3
def calc_fib(n):

    # if n is 1 or 0 return n
    if (n <= 1):
        return n

    # else calculate fibonacci number
    a, b = 0, 1
    for _ in range(2, n+1):
        a, b = b, a + b

    return b

if __name__ == '__main__':
    
    # get input from user
    n = int(input())
    print(calc_fib)