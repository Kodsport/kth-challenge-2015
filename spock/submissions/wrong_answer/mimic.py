import sys

def make_move(m):
    sys.stdout.write('%s\n' % m)
    sys.stdout.flush()
    return sys.stdin.readline().strip()

rounds = int(sys.stdin.readline())
m = make_move("rock")
for i in range(rounds-1): m = make_move(m)
