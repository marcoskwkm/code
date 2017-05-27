for test in xrange(int(raw_input())):
    raw_input()
    s = filter(lambda c: c != '.', raw_input())
    print 'Valid' if len(s) % 2 == 0 and s == 'HT' * (len(s) / 2) else 'Invalid'
