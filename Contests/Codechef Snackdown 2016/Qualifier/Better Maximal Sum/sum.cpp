#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int) 1e5 + 10;

int v[MAXN];
lint best_l[MAXN], best_r[MAXN];

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        int n;
        scanf("%d", &n);
        lint ans = -LINF;
        for (int i = 1; i <= n; i++) {
            scanf("%d",  &v[i]);
            best_l[i] = best_r[i] = v[i];
            if (best_l[i - 1] > 0)
                best_l[i] += best_l[i - 1];
            ans = max(ans, best_l[i]);
        }
        best_r[n + 1] = 0;
        for (int i = n; i >= 0; i--)
            if (best_r[i + 1] > 0)
                best_r[i] += best_r[i + 1];
        for (int i = 1; i <= n; i++)
            if (best_l[i - 1] > 0 && best_r[i + 1] > 0)
                ans = max(ans, best_l[i - 1] + best_r[i + 1]);
        printf("%lld\n", ans);
    }        
    return 0;
}
