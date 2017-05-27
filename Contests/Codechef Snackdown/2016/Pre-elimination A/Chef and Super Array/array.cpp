#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MOD = (int)1e9 + 7;
const int MAXP = 35, MAXN = (int)1e5 + 10;

lint pot3[MAXP];

lint solve(lint val, lint pos, int m, lint x, lint y) {
    lint length = (1 << m) - 1;
    if (x <= pos - length  && pos + length <= y)
        return (pot3[m] * val) % MOD;
    if (pos - length > y || pos + length < x)
        return 0;
    return (solve(val, pos - (1 << (m - 1)), m - 1, x, y) +
            solve(val, pos, m - 1, x, y) +
            solve(val, pos + (1 << (m - 1)), m - 1, x, y)) % MOD;
}

int main() {
    pot3[0] = 1;
    for (int i = 1; i < MAXP; i++)
        pot3[i] = pot3[i - 1] * 3 % MOD;
    int t;
    for (scanf("%d", &t); t--;) {
        int n, m;
        lint x, y, ans = 0;
        scanf("%d%d%lld%lld", &n, &m, &x, &y);
        lint q = 1; 
        for (int i = 1; i <= n; i++) {
            int val;
            scanf("%d", &val);
            ans += solve(val, q, m, x, y);
            ans %= MOD;
            q += (1 << m);
        }
        printf("%lld\n", ans);
    }
    return 0;
}
