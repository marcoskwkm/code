T = int(input())


def check(n):
    s = str(n)
    return s == s[::-1]


for t in range(1, T + 1):
    n = int(input())
    d = 1
    ans = 0
    while d * d <= n:
        if n % d == 0:
            if check(d):
                ans += 1

            if d * d < n and check(n // d):
                ans += 1
        d += 1
    print(f'Case #{t}: {ans}')
