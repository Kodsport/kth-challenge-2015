#!/usr/bin/env python3
# Assumes "ulimit -s unlimited"
import sys

def dfs(u, p):
    if vis[u] > 0: return True
    vis[u] = 1
    for (v,e) in adj[u]:
        if e != p:
            if dfs(v,e):
                print('%d %d' % (u,v))
                return True
            else:
                print('%d %d' % (v,u))
    vis[u] = -1
    return False

IN = list(map(int, sys.stdin.read().split()))
N = IN[0]
vis = [0]*(N+1)
adj = [[] for i in range(N+1)]
for i in range(2*N): adj[IN[1+i]].append((IN[1+(i^1)],i//2))

sys.setrecursionlimit(N+10)
for u in range(1,N+1): 
    if vis[u] == 0: dfs(u,-1)
