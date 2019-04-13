def gcd(a, b): return a if not b else gcd(b, a % b)

T = int(raw_input())
for test_case in xrange(1, T + 1):
    _, L = map(int, raw_input().split())
    v = map(int, raw_input().split())
    for i in xrange(L - 1):
        if v[i] != v[i + 1]:
            p, idx = gcd(v[i], v[i + 1]), i
            break

    sol = [0] * (L + 1)
    sol[idx + 1] = p
    primes = set([p])
    for i in xrange(idx + 1, L):
        sol[i + 1] = v[i] / sol[i]
        primes.add(sol[i + 1])
    for i in xrange(idx, -1, -1):
        sol[i] = v[i] / sol[i + 1]
        primes.add(sol[i])

    p_list = sorted(list(primes))
    m = {}
    for i in xrange(len(p_list)):
        m[p_list[i]] = chr(ord('A') + i)

    print 'Case #%d: ' % test_case + ''.join(map(lambda x: m[x], sol))
