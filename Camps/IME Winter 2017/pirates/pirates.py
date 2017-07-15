import sys

hi = 0
primes = []
x = 1

for p in range(2, 100):
    ok = 1
    d = 2
    while d*d <= p:
        if p % d == 0:
            ok = 0
        d += 1
    if ok == 1: primes.append(p)

def go(i, lim, cur, nd, n):
    global hi
    if cur > n: return
    hi = max(hi, nd)
    take = 0
    while take < lim:
        cur *= primes[i]
        take += 1
        go(i + 1, take, cur, nd * (take + 1), n)

ans = 10**20

def go2(i, lim, cur, nd):
    global ans
    if nd > hi:
        ans = min(ans, cur)
        return
    take = 0
    while take < lim:
        cur *= primes[i]
        take += 1
        go2(i + 1, take, cur, nd * (take + 1))

n = int(input())
go(0, 80, 1, 1, n)
go2(0, 80, 1, 1)
print(ans)
