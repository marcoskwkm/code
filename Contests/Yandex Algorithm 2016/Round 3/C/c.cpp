#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXM = (int)1e6 + 10;
const int MAXN = (int)1e5 + 10;

bool done[MAXM];
int a[MAXN], b[MAXN], c[MAXN];
lint sumb[MAXN];
lint req[MAXN];

int main() {
    int n;
    lint M;
    scanf("%d%lld", &n, &M);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d", &a[i], &b[i], &c[i]);
        sumb[i] = sumb[i - 1] + b[i];
        req[i] = max(req[i - 1], a[i] - sumb[i - 1]);
    }
    lint ans = 0;
    while (1) {
        done[M] = 1;
        int l = 1, r = n + 1;
        while (l < r) {
            int mid = (l + r)/2;
            if (M <= req[mid]) r = mid;
            else l = mid + 1;
        }
        ans += l;
        if (l == n + 1) break;
        M += sumb[l - 1] - c[l];
        M = max(M, 0ll);
        if (done[M]) {
            printf("-1\n");
            return 0;
        }
    }
    printf("%lld\n", ans - 1);    
    return 0;
}
