import random
import sys

MOVE = ["rock","paper","scissors","lizard","Spock"]

def make_move(i):
    sys.stdout.write('%s\n' % MOVE[i])
    sys.stdout.flush()
    sys.stdin.readline()

rounds = int(sys.stdin.readline())
for i in range(rounds): make_move(random.randint(0,4))
