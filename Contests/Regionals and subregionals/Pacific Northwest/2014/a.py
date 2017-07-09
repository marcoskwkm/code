import sys
n = int(raw_input())
for line in sys.stdin.readlines():
    takezero = True
    ops = line.strip()
    for op in '+*-=':
        ops = ops.replace(op, ';')
    ops = ops.split(';')
    for x in ops:
        if x != "" and x[0] == '?' and x != "?":
            takezero = False
    found = 0
    for d in xrange(ord('0'), ord('9') + 1):
        if chr(d) == '0' and not takezero: continue
        if chr(d) in line: continue
        l, r = line.replace('?', chr(d)).split('=')
        if eval(l) == eval(r):
            found = 1
            print chr(d)
            break
    if found == 0:
        print -1
