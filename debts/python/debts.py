#!/usr/bin/env python3

################################################################################
#                                                                              #
#   Filename    : debts.py                                                     #
#   Project     : Debts                                                        #
#   Version     : 1.0                                                          #
#   Author      : Spiros Dontas                                                #
#   Email       : spirosdontas@gmail.com                                       #
#                                                                              #
#   Description : ICPC NTUA                                                    #
#                                                                              #
################################################################################

N, M = (int(s) for s in input().split())

needed = {}

for i in range(1, N + 1) :
    needed[i] = {}

for i in range(M) :
    P, X1, T1, X2, T2 = (int(s) for s in input().split())
    if not T1 in needed[X1] :
        needed[X1][T1] = -P
    else :
        needed[X1][T1] -= P
    if not T2 in needed[X2] :
        needed[X2][T2] = P
    else :
        needed[X2][T2] += P

for k, v in needed.items() :
    needed[k] = sorted(needed[k].items())

#  print(sorted(needed.items()))

for i in range(1, N + 1) :
    start = 0
    current = 0
    for k, v in needed[i] :
        current += v
        if current < 0 :
            start += -current
            current = 0
        # end if
    # end for
    if i < N :
        print(start, end=" ")
    else :
        print(start)
# end for
