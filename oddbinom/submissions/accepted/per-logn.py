#!/usr/bin/env python3
import sys

n = int(sys.stdin.read())
b = ans = 0
for p in range(50, -1, -1):
    if n & (1<<p):
        ans += 2**b*3**p
        b += 1
print(ans)
