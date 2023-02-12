import sys

n = int(sys.stdin.read())
T2 = [1]*n
p = 1
for i in range(1, n):
    if i >= 2*p: p *= 2
    T2[i] = T2[p-1] + 2*T2[i%p]
print T2[n-1]
