#!/usr/bin/python3
from sys import stdin
import re
import sys

integer = "(0|-?[1-9]\d*)"
oneint = re.compile(integer + "\n")
ints = re.compile("(" + integer + " )*" + integer + "\n")

line = stdin.readline()
assert oneint.match(line)
n = int(line)
assert 2 <= n <= 30


line = stdin.readline()
assert ints.match(line)
m = list(map(int, line.split()))
assert len(m) == n-1
assert max(m) <= 10**9
assert min(m) >= 0
assert m[-1] > 0

assert len(stdin.readline()) == 0
sys.exit(42)
