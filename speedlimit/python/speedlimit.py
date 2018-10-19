#!/usr/bin/env python3

################################################################################
#                                                                              #
#   Filename    : speedlimit.py                                                #
#   Project     : Speedlimit                                                   #
#   Version     : 1.0                                                          #
#   Author      : Spiros Dontas                                                #
#   Email       : spirosdontas@gmail.com                                       #
#                                                                              #
#   Description : ICPC NTUA                                                    #
#                                                                              #
################################################################################

import queue, sys

N, M, D = (int(s) for s in input().split())

neighbors = []
best = []

for i in range(N) :
    neighbors.append([])
    best.append([])
    for j in range(501) :
        best[i].append(sys.float_info.max)

for i in range(M) :
    fr, to, v, l = (int(s) for s in input().split())
    neighbors[fr].append((fr, to, v, l, []))

start = 0
end = D
minimum = sys.float_info.max
previous = []

remaining = queue.PriorityQueue()

for state in neighbors[start] :
    fr, to, v, l, _ = state
    if v == 0 :
        v = 70
    remaining.put((l / v, (fr, to, v, l, [start])))
    best[to][v] = l / v
# end for

while not remaining.empty() :
    cost, (fr, to, v, l, prev) = remaining.get()
    if to == end :
        if cost < minimum :
            minimum = cost
            previous = list(prev)
            previous.append(to)
        # end if
        continue
    # end if
    for neighbor in neighbors[to] :
        nfr, nto, nv, nl, _ = neighbor
        if nv == 0 :
            nv = v
        if nl / nv + cost < best[nto][nv] :
            best[nto][nv] = nl / nv + cost
            newprev = list(prev)
            newprev.append(to)
            remaining.put((nl / nv + cost, (nfr, nto, nv, nl, newprev)))
        # end if
    # end for
# end while

for i in range(len(previous)) :
    if i < len(previous) - 1 :
        print(previous[i], end=" ")
    else :
        print(previous[i])
