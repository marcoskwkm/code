#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

lint gcd(lint a, lint b) { return b ? gcd(b, a%b) : a; }

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        lint a, b, c, d;
        scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
        lint g = gcd(c, d);
        a %= g; b %= g;
        if (a < b) swap(a, b);
        printf("%lld\n", min(a - b, b + g - a));
    }        
    return 0;
}
