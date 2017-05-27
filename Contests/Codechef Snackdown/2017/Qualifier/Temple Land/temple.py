for t in xrange(int(raw_input())):
    n = int(raw_input())
    print 'yes' if all(map(lambda (i, h): h == min(i + 1, n - i), enumerate(map(int, raw_input().split())))) and n % 2 else 'no'
