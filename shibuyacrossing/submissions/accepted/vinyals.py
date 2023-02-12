#!/usr/bin/env python3

import sys
from bisect import bisect

def lis(v) :
    s = []
    for x in v:
        i=bisect(s,-x)
        if i>=len(s) : s.append(-x)
        else : s[i]=-x
    return len(s)

N,M = map(int,sys.stdin.readline().split())
sigma = list(range(N))
for i in range(M):
    a,b=map(lambda x : int(x)-1,sys.stdin.readline().split())
    if (a>b) : a,b=b,a
    sigma[a]+=1
    sigma[b]-=1
sigmainv=[0]*N
for i,x in enumerate(sigma) : sigmainv[x]=i
print(lis(sigmainv))
