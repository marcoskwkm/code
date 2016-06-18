t = int(raw_input())
for test_case in xrange(t):
    raw_input()
    expr = raw_input()
    true_expr = ""
    can_0 = False
    for c in expr:
        if ord('1') <= ord(c) <= ord('9'):
            true_expr += c
            can_0 = True
        elif c == '0' and can_0:
            true_expr += c
    print true_expr if len(true_expr) > 0 else "0"
