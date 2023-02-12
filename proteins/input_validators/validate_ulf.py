#!/usr/bin/python3
from sys import stdin
import re
import sys

integer = "(0|-?[1-9]\d*)"
oneint = re.compile(integer + "\n")

line = stdin.readline()
assert oneint.match(line)
n = int(line)
assert 1 <= n <= 10**6

DNA = re.compile("[ATGC]+\n")
line = stdin.readline()
assert DNA.match(line)
assert len(line) <= 1000+1

assert len(stdin.readline()) == 0
sys.exit(42)
