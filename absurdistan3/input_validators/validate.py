#!/usr/bin/python3
from sys import stdin
import re
import sys

integer = "(0|-?[1-9]\d*)"
oneint = re.compile(integer + "\n")
twoint = re.compile(integer + " " + integer + "\n")

line = stdin.readline()
assert oneint.match(line)
n = int(line)
assert 1 <= n <= 10 ** 5

for test in range(n):
    line = stdin.readline()
    assert twoint.match(line)
    a, b = list(map(int, line.split()))
    assert 1 <= a <= n and 1 <= b <= n and a != b

assert len(stdin.readline()) == 0
sys.exit(42)
