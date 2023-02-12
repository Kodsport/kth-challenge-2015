#!/usr/bin/env python3
import sys
sys.setrecursionlimit(5000)

PAT = ['ATG','AT','AG','TG','A','T','G']

(n,dna) = sys.stdin.read().split()
L = len(dna)

cost = [[[None]*(L+1) for j in range(3)] for i in range(L)]

def Cost(i, s, n):
    global cost
    if n == 0:
        return 0
    if n > L-i:
        return Cost(i, s, L-i)+3*(n-(L-i))
    if cost[i][s][n] is None:
        cost[i][s][n] = min([(3-s)%3 + 3 - len(p) + Cost(i+len(p), 0, n-1)
                             for p in PAT if i+len(p) <= L and dna[i:i+len(p)] == p] +
                            [Cost(i+1, (s+1)%3, n)])
    return cost[i][s][n]
    
print(Cost(0, 0, int(n)))
