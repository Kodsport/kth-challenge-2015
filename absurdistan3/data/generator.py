#!/usr/bin/env python3
import random
from sys import stdin


def push(g, e):
    if random.randint(0, 1) == 1:
        e = (e[1], e[0])
    g.append(e)

s = stdin.readline().strip().split()
pos = 2
if s[0] == "exactly":
    n = int(s[1])
else:
    n = random.randint(int(s[1]), int(s[2]))
    pos += 1

assert n >= 2
print(n)

a = [i for i in range(n)]
random.shuffle(a)
typ = s[pos]
g = []
if typ == "randgraph":
    for j in range(1, n):
        edge = (a[random.randint(0, j - 1)], a[j])
        push(g, edge)

    x, y = random.randint(0, n - 1), random.randint(0, n - 2)
    if y >= x:
        y += 1
    edge = (a[x], a[y])
    push(g, edge)
elif typ == "cycle":
    for i in range(n):
        edge = (a[i], a[(i + 1) % n])
        push(g, edge)
elif typ == "line":
    for j in range(1, n):
        edge = (a[j - 1], a[j])
        push(g, edge)

    x, y = random.randint(0, n - 1), random.randint(0, n - 2)
    if y >= x:
        y += 1
    edge = (a[x], a[y])
    push(g, edge)
elif typ == "star":
    for j in range(1, n):
        edge = (a[0], a[j])
        push(g, edge)

    x, y = random.randint(1, n - 1), random.randint(1, n - 2)
    if y >= x:
        y += 1
    edge = (a[x], a[y])
    push(g, edge)
elif typ == "disconnected":
    for j in range(n):
        q = random.randint(0, n - 2)
        if q >= j:
            q += 1
        edge = (a[q], a[j])
        push(g, edge)

random.shuffle(g)
for x in g:
    if random.randint(0, 1) == 0:
        print(x[1] + 1, x[0] + 1)
    else:
        print(x[0] + 1, x[1] + 1)
