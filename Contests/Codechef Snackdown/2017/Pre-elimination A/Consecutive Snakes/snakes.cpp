#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;

lint v[MAXN];
lint d[MAXN];

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        lint n, len, L, R;
        scanf("%lld%lld%lld%lld", &n, &len, &L, &R);
        for (int i = 0; i < n; i++)
            scanf("%lld", &v[i]);
        sort(v, v + n);
        for (int i = 0; i < n; i++)
            d[i] = L + len*i - v[i];
        sort(d, d + n);
        lint delta = max(0ll, min(R - L - n * len, -d[n / 2]));
        lint ans = 0;
        for (int i = 0; i < n; i++)
            ans += abs(L + len*i + delta - v[i]);
        printf("%lld\n", ans);
    }        
    return 0;
}
