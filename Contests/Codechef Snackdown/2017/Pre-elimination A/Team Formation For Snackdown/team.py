for t in xrange(int(raw_input())):
    n, m = map(int, raw_input().split())
    for x in xrange(m): raw_input()
    print 'yes' if n % 2 == 0 else 'no'
    
