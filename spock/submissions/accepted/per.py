#!/usr/bin/env python3
import sys

DEBUG=True

P = 127
MOVE = ["rock","paper","scissors","lizard","Spock"]
INVMOVE = dict((MOVE[i],i) for i in range(5))
lose = [[1,4],
        [2,3],
        [0,4],
        [0,2],
        [1,3]]
history = []

class State:
    def __init__(self, x, a, b):
        self.x = x
        self.a = a
        self.b = b
    def advance(self): 
        self.x = (self.a*self.x+self.b) % P

def make_move(i):
    global history
    sys.stdout.write('%s\n' % MOVE[i])
    sys.stdout.flush()
    history.append(INVMOVE[sys.stdin.readline().strip()])
    if DEBUG:
        sys.stderr.write('[DEBUG %s]: made move %d got move %d\n' % (__file__, i, history[-1]))

PREROUNDS = 2

rounds = int(sys.stdin.readline())
if DEBUG:
    sys.stderr.write('[DEBUG %s]: play for %d rounds\n' % (__file__, rounds))

for i in range(PREROUNDS): make_move(4)

cands = []
if history[0] == history[1]:
    cands.append(State(history[0], 0, history[0]))
for x1 in range(history[0], P, 5):
    for x2 in range(history[1], P, 5):
        if x1 == x2: continue
        for a in range(0, P):
            b = (x2-a*x1) % P
            cands.append(State(x2, a, b))

for r in range(PREROUNDS, rounds):
    poss = [0]*5
    for S in cands:
        prev = S.x
        S.advance()
        poss[lose[S.x % 5][0]] += 1
        poss[lose[S.x % 5][1]] += 1
    if DEBUG:
        sys.stderr.write('[DEBUG %s]: move %d: have %d cands predicting %s}\n' % (__file__, r+1, len(cands), poss))
    make_move(max(enumerate(poss), key=lambda x: x[1])[0])
    cands = [S for S in cands if S.x % 5 == history[-1]]
