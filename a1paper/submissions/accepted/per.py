#!/usr/bin/env python3
import sys
import math
import functools

(cost,rem,_) = functools.reduce(lambda x,n: (x[0]+x[1]*x[2], max(0,2*x[1]-n), x[2]/math.sqrt(2.0)),
                      map(int, sys.stdin.read().split()[1:]), (0,1,1))
print(cost*math.pow(2,-0.75) if rem == 0 else "impossible")
