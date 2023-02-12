#!/usr/bin/env python3
import sys

V = list(map(int, sys.stdin.read().split()[1:]))
R = [(v,i+1) for (i,v) in enumerate(V) if V.count(v) == 1]
print(max(R)[1] if len(R) > 0 else "none")

