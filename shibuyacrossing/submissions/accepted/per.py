#!/usr/bin/env python3
import bisect, sys

IN = list(map(int, sys.stdin.read().split()))
N = IN[0]
E = set(zip(IN[2::2]+IN[3::2], IN[3::2]+IN[2::2]))
b = [0]*N
from functools import cmp_to_key
for v in sorted(range(1,N+1), key = cmp_to_key(lambda x,y: 1-2*(((x,y) in E) ^ (x<y)))):
    b[bisect.bisect(b, -v)] = -v
print(N-b.count(0))
