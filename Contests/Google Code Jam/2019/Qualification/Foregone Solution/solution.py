t = int(raw_input())
for test_case in xrange(1, t + 1):
    n = list(raw_input())
    x, y = n[:], n[:]
    for i in xrange(len(x)):
        if x[i] == '4':
            x[i] = y[i] = '2'
        else:
            y[i] = '0'
    print 'Case #%d: ' % test_case + str(int(''.join(x))) + ' ' + str(int(''.join(y)))
