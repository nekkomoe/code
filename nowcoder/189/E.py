arr = raw_input().split()
n = (2 ** int(arr[0]))
m = (2 ** int(arr[1])) - 1
def calc(n):
    if n <= 0:
        return 0
    return ((n - 1) / 7) + 1
 
print(calc(m) - calc(n - 1))
