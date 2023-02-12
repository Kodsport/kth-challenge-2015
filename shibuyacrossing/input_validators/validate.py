#!/usr/bin/python3
from sys import stdin
import re
import sys

integer = "(0|-?[1-9]\d*)"
twoint = re.compile(integer + " " + integer + "\n")

line = stdin.readline()
assert twoint.match(line)
n, m = list(map(int, line.split()))
assert 1 <= n <= 800
assert 0 <= m <= 10000

pairs = set()
for test in range(m):
    line = stdin.readline()
    assert twoint.match(line)
    a, b = list(map(int, line.split()))
    assert 1 <= a < b and 1 <= b <= n
    assert (a, b) not in pairs
    pairs.add((a, b))

assert len(stdin.readline()) == 0
sys.exit(42)
