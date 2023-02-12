#!/usr/bin/env python3
from sys import stdin
import re
import sys

integer = "(0|-?[1-9]\d*)"
oneint = re.compile(integer + "\n")
manyint = re.compile("(" + integer + " )*" + integer + "\n")

line = stdin.readline()
assert oneint.match(line)
n = int(line)
assert 1 <= n <= 1000

line = stdin.readline()
assert manyint.match(line)
a = list(map(int, line.split()))
assert len(a) == n
for x in a:
    assert 0 < x <= n

assert len(stdin.readline()) == 0
sys.exit(42)
