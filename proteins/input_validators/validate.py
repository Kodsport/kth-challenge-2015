from sys import stdin
import re
import sys

posint = re.compile('([1-9]\d*)\n')
DNAstr = re.compile('[ACGT]+\n')

# number of bit sweeps
n = stdin.readline()
assert posint.match(n)
n = int(n)
assert 1 <= n <= 10 ** 6

line = stdin.readline()
assert DNAstr.match(line)
assert len(line) <= 1001

sys.exit(42)
