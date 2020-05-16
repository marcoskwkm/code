def calc1(at, take): return (2 * at + take - 1) * take / 2
def calc2(at, take): return (at + take - 1) * take

def find2(cakes, at):
    l, r = 0, 2*10**9
    while l < r:
        m = (l + r + 1) / 2
        if cakes - calc2(at, m) >= 0:
            l = m
        else:
            r = m - 1
    return l, calc2(at, l)

T = int(raw_input())
for t in xrange(1, T + 1):
    pancakes = map(int, raw_input().split())
    cur = 0 if pancakes[0] >= pancakes[1] else 1

    at = 1
    l, r = 0, 2*10**9
    while l < r:
        m = (l + r + 1) / 2
        q = calc1(at, m)

        if cur == 0:
            if pancakes[cur] - q >= pancakes[cur ^ 1]:
                l = m
            else:
                r = m - 1
        else:
            if pancakes[cur] - q > pancakes[cur ^ 1]:
                l = m
            else:
                r = m - 1
    if pancakes[cur] - calc1(at, l + 1) >= 0: l += 1
    pancakes[cur] -= calc1(at, l)
    cur ^= 1
    at += l

    q0, take0 = find2(pancakes[0], at if cur == 0 else at + 1)
    q1, take1 = find2(pancakes[1], at if cur == 1 else at + 1)

    print 'Case #%d: %d %d %d' % (t, at + q0 + q1 - 1, pancakes[0] - take0, pancakes[1] - take1)
