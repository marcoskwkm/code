k = map(int, raw_input().split())[1]
v = map(int, raw_input().split())

v = v[::-1]
while v[-1] == 0: v.pop()
v = v[::-1]

def choose(n, k):
    r = 1
    k = min(k, n - k)
    for i in xrange(k):
        r *= n - i
    for i in xrange(1, k + 1):
        r /= i
    return r

def get(v, k):
    s = 0
    for i in xrange(len(v)):
        s += choose(k + i - 1, i) * v[len(v) - 1 - i]
    return s

if max(v) >= k:
    print 0
    
elif len(v) <= 5:
    l, r = 1, 10**18
    while l < r:
        m = (l + r) / 2
        if get(v, m) >= k: r = m
        else: l = m + 1
    print l
    
else:
    i = 1
    while True:
        if sum(v) >= k:
            break
        for j in xrange(1, len(v)):
            v[j] += v[j - 1]
        i += 1
    print i
