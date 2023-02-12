#!/usr/bin/env python3
from sys import stdin

def possible(board):
    if len(board) == 1:
        board = board[0]
        for i in range(len(board)-3):
            for t in [3,2,1,0]:
                board[i+t] ^= board[i]
        return 1 not in board
    return sum(sum(board,[])) % (2+2*(len(board[0])==2)) == 0

(m,n) = list(map(int, stdin.readline().split()))
board = [[{'X':1,'.':0}[c] for c in stdin.readline()[:-1]] for i in range(m)]
if n <= m:
    board = [[r[j] for r in board] for j in range(n)]

print("possible" if possible(board) else "impossible")

