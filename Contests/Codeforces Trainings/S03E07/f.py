n, target = map(int, raw_input().split())
v = map(int, raw_input().split())
s = sum(v)

ans = 10**18
cur_h = 0
sv = 0
for i in xrange(n):
    if cur_h >= target:
        ans = min(ans, i)
        break;
    l, r = 0, (2*10**9 + 10) / n
    while l < r:
        k = (l + r) / 2
        h = (k * n + i) * (k * n + i + 1) / 2 + k * s + sv
        if h >= target:
            r = k
        else:
            l = k + 1            
    ans = min(ans, l * n + i)
    cur_h += v[i] + i + 1
    sv += v[i]

print ans
