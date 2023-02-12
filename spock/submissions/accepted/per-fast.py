# This solution contains several optimizations that should not be
# needed, trying to see how quick I can make the Python solution
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

MODINV = [0]*2*P
for i in range(1,P):
    for j in range(1,P):
        if (i*j) % P == 1:
            MODINV[i] = MODINV[i+P] = j
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

PREROUNDS = 7

rounds = int(sys.stdin.readline())
if DEBUG:
    sys.stderr.write('[DEBUG %s]: play for %d rounds\n' % (__file__, rounds))

for i in range(PREROUNDS): make_move(4)

cands = []
all_same = False
if history[0] == history[1] == history[2] == history[3]:
    all_same = True
    cands.append(State(history[0], 0, history[0]))
for x1 in range(history[0], P, 5):
    for x2 in range(history[1], P, 5):
        if x1 == x2: continue
        MI = MODINV[P+x2-x1]
        for x3 in range(history[2], P, 5):
            if x2 == x3: continue
            if x1 == x3 and all_same: continue
            a = (x3-x2)*MI % P
            b = (x2-a*x1) % P
            x = x3
            H = [x1,x2,x3]
            for i in range(3, PREROUNDS):
                x = (a*x+b) % P
                if x % 5 != history[i]: break
                if x in H and all_same: break
                H.append(x)
            else:
                if not all_same or (a*x+b) not in H:
                    cands.append(State(x, a, b))



for r in range(PREROUNDS, rounds):
    poss = [0]*5
    shorts = 0
    for S in cands:
        prev = S.x
        S.advance()
        if ((S.a*S.x+S.b) % P == prev): shorts += 1
        poss[lose[S.x % 5][0]] += 1
        poss[lose[S.x % 5][1]] += 1
    if DEBUG:
        sys.stderr.write('[DEBUG %s]: move %d: have %d cands, %d shorts predicting %s}\n' % (__file__, r+1, len(cands), shorts, poss))
    make_move(max(enumerate(poss), key=lambda x: x[1])[0])
    cands = [S for S in cands if S.x % 5 == history[-1]]

#for C in cands:
#    sys.stderr.write('a = %d, b = %d, x = %d\n'  % (C.a,C.b,C.x))
#print cands
