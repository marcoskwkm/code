#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef pair<pii, pii> ppp;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;

void add(set<ppp> &s, pii p, int c, int t) {
    ppp add(p, pii(c, t));
    auto it = s.lower_bound(add);
    while (it != s.end() && it->first.second <= p.second)
        it = s.erase(it);
    if (it != s.end() && it->first.first <= p.second) {
        ppp oldp = *it;
        it = s.erase(it);
        oldp.first.first = p.second + 1;
        it = s.insert(oldp).first;
    }
    if (it != s.begin() && prev(it)->first.second >= p.first) {
        ppp oldp = *prev(it);
        s.erase(prev(it));
        if (oldp.first.second > p.second)
            s.insert(ppp(pii(p.second + 1, oldp.first.second), oldp.second));
        oldp.first.second = p.first - 1;
        s.insert(oldp);
    }
    s.insert(add);
    // for (ppp x: s) {
    //     printf("(%d, %d) - (%d, %d)\n", x.first.first, x.first.second, x.second.first, x.second.second);
    // }
}

pii get(set<ppp> &s, int pos) {
    ppp foo(pii(pos, INF), pii(0, 0));
    auto it = s.upper_bound(foo);
    assert(it != s.begin());
    return prev(it)->second;
}

int main() {
    int n, m, q;
    scanf("%d%d%d", &n, &m, &q);
    set<ppp> h, v;
    add(h, pii(1, n), 0, -1);
    add(v, pii(1, m), 0, -1);
    
    for (int t = 0; t < q; t++) {
        char op;
        scanf(" %c", &op);
        if (op == 'H') {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            add(h, pii(a, b), c, t);
        }
        else if (op == 'V') {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            add(v, pii(a, b), c, t);
        }
        else {
            int r, c;
            scanf("%d%d", &r, &c);
            pii pr = get(h, r);
            pii pc = get(v, c);
            // printf("(%d, %d) x (%d, %d)\n", pr.first, pr.second, pc.first, pc.second);
            if (pr.second > pc.second) printf("%d\n", pr.first);
            else printf("%d\n", pc.first);
        }
    }    
    return 0;
}
