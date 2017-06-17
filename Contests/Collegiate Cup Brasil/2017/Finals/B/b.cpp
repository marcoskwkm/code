#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)3e5 + 10;
const int LOG = 20;

int v[MAXN];
int nxt_r[MAXN], nxt_l[MAXN];

lint m[MAXN];
lint rmq[LOG][MAXN];
int n;

// Builds RMQ structure for array v of size n in O(n*log(n))
void build_rmq() {
    for (int i = 0; i < n; i++)
        rmq[0][i] = m[i];
    for (int log = 1; log < LOG; ++log) {
        for (int i = 0; i < n; i++) {
            rmq[log][i] = max(rmq[log-1][i], rmq[log-1][min(n-1, i + (1<<(log-1)))]);
        }
    }
}
// l e r inclusives
lint get_rmq(int l, int r) {
    int len = r - l + 1;
    int bit = 31 - __builtin_clz(len);
    return max(rmq[bit][l], rmq[bit][r - (1<<bit) + 1]);
}

lint get_value(int l, int r) {
    lint len = r - l + 1;
    len = min<lint>(len, v[l] + 1);
    return len * v[l] - len * (len - 1) / 2;
}    

int main() {
    int q;
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", &v[i]);
    nxt_l[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (v[i - 1] == v[i])
            nxt_l[i] = nxt_l[i - 1];
        else
            nxt_l[i] = i;
    }
    nxt_r[n] = n;
    for (int i = n - 1; i >= 1; i--) {
        if (v[i + 1] == v[i])
            nxt_r[i] = nxt_r[i + 1];
        else
            nxt_r[i] = i;
    }

    lint last = 0;
    for (int i = 1; i <= n; i++) {
        lint val = get_value(i, nxt_r[i]);
        for (int j = i; j <= nxt_r[i]; j++)
            m[j] = val;
        i = nxt_r[i];
    }

    build_rmq();
    while (q--) {
        int l, r;
        scanf("%d%d", &l, &r);
        if (nxt_r[l] > r || nxt_l[r] < l) {
            printf("%lld\n", get_value(l, r));
            continue;
        }
        lint ans = max(get_value(l, nxt_r[l]), get_value(nxt_l[r], r));
        l = nxt_r[l] + 1, r = nxt_l[r] - 1;
        if (l <= r) ans = max(ans, get_rmq(l, r));
        printf("%lld\n", ans);
    }        
    return 0;
}
