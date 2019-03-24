#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

lint solve(lint p, lint q, lint n) {
    lint qq = p / q;
    lint ans = n * (n + 1) / 2 * qq;
    p %= q;
    if (!p) return ans;
    lint m = n * p / q;
    return ans + n * m - solve(q, p, m) + n / q;
}    

int main() {
    int t;
    for (cin >> t; t--;) {
        lint p, q, n;
        scanf("%lld%lld%lld", &p, &q, &n);
        lint d = __gcd(p, q);
        printf("%lld\n", n * (n + 1) / 2 * p - q * solve(p / d, q / d, n));
    }
    return 0;
}
