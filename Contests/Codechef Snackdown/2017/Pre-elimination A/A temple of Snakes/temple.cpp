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
const int LOG = 20;

int v[MAXN];
int vl[MAXN], vr[MAXN];

int rmq[2][LOG][MAXN];

void build_rmq(int k, int *vv, int n) {
    for (int i = 1; i <= n; i++) rmq[k][0][i] = vv[i];
    for (int l = 1; l < LOG; l++)
        for (int i = 1; i <= n; i++)
            rmq[k][l][i] = min(rmq[k][l - 1][i],
                               rmq[k][l - 1][min(n, i + (1 << (l - 1)))]);
}

int get_rmq(int k, int l, int r) {
    int len = r - l + 1;
    int bit = 31 - __builtin_clz(len);
    return min(rmq[k][bit][l], rmq[k][bit][r - (1 << bit) + 1]);
}

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        int n;
        scanf("%d", &n);
        lint sum = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &v[i]);
            sum += v[i];
            vl[i] = v[i] - i;
            vr[i] = v[i] - (n - i);
        }
        build_rmq(0, vl, n);
        build_rmq(1, vr, n);
        lint ans = LINF;
        for (int x = 1; x <= n; x++) {
            int l = 0, r = n;
            while (l < r) {
                int mid = (l + r + 1)/2;
                if (x - mid < 1 || x + mid > n) r = mid - 1;
                else {
                    int low_l = get_rmq(0, x - mid, x);
                    int low_r = get_rmq(1, x, x + mid);
                    if (low_l < (mid + 1) - x || low_r < (mid + 1) - (n - x))
                        r = mid - 1;
                    else
                        l = mid;
                }
            }
            ans = min(ans, sum - lint(l + 1)*(l + 1));
        }
        printf("%lld\n", ans);
    }        
    return 0;
}
