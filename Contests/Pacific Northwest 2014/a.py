import sys
n = int(raw_input())
for line in sys.stdin.readlines():
    try:
        takezero = True
        ops = line.replace('+',';').replace('*',';').replace('-',';').replace('=',';').split(';')
        for x in ops:
            if x != "" and x[0] == '?':
                if x != "?":
                    takezero = False
        line = line.split('=')
        lhs, rhs = line[0], line[1]
        found = 0
        for d in xrange(ord('0'), ord('9') + 1):
            if chr(d) == '0' and not takezero: continue
            if d in line: continue
            l = lhs.replace('?', chr(d))
            r = rhs.replace('?', chr(d))
            if eval(l) == eval(r):
                found = 1
                print chr(d)
                break
        if found == 0:
            print -1
    except:
        continue
