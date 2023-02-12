#!/usr/bin/env python3
import textwrap
import random

def gen(m,n,mask):
    binstr="{:0{}b}".format(mask,m*n)
    boardstr=binstr.translate(str.maketrans('01','.X'))
    file="secret/small-{}{}-{}.in".format(m,n,binstr)
    with open(file,'w') as f:
        print(m,n,file=f)
        print(textwrap.fill(boardstr, width=n),file=f)

def genall(m,n):
    for mask in range(2**(m*n)):
        gen(m,n,mask)

def genrand(m,n,p):
    mask=0
    for bit in range(m*n):
        mask<<=1
        if (random.random()<p) : mask|=1
    gen(m,n,mask)

def gensome(m,n):
    gen(m,n,0)
    gen(m,n,2**(m*n)-1)
    for case in range(10):
        genrand(m,n,.5)
        genrand(m,n,.75)
        
genall(1,1)
genall(1,2)
genall(1,3)
genall(2,1)
genall(3,1)
genall(2,2)
genall(2,3)
gensome(1,4)
gensome(4,4)
gensome(5,5)
gensome(1,5)
