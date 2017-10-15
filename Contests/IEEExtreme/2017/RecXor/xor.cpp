#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

lint get_xor(lint n) {
    n++;
    lint ret = 0;
    for (int i = 0; (1LL << i) <= n; i++) {        
        bool add = 0;
        if (i == 0) add = (n >> 1) & 1;
        else {
            lint nn = n & ((1LL << (i + 1)) - 1);
            add = max(0LL, nn - (1LL << i)) & 1;
        }
        if (add) ret |= (1LL << i);            
    }
    return ret;
}

inline lint get_xor(lint l, lint r) {
    return get_xor(r) ^ get_xor(l - 1);
}

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        lint l, h, n, d1, d2;
        scanf("%lld%lld%lld%lld%lld", &l, &h, &n, &d1, &d2);
        lint ans = get_xor(n, n + l*h - 1);
        lint r1 = (d1 - n) / l, c1 = (d1 - n) % l;
        lint r2 = (d2 - n) / l, c2 = (d2 - n) % l;
        if (r1 > r2) swap(r1, r2);
        if (c1 > c2) swap(c1, c2);
        for (int r = r1; r <= r2; r++) {
            // debug("%lld %lld\n", n + r*l + c1, n + r*l + c2);
            ans ^= get_xor(n + r*l + c1, n + r*l + c2);
        }
        printf("%lld\n", ans);
    }        
    return 0;
}
