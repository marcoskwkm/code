from random import randint

n = 30000
print n
v = [randint(1, 10**9) for x in xrange(n)]
print ' '.join(map(str, v))

q = 200000
print q
for x in xrange(q):
    i, j, k = randint(1, n), randint(1, n), randint(1, 1000000000)
    if i > j: i, j = j, i
    print i, j, k
