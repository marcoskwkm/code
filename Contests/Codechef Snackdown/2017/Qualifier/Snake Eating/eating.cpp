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

int v[MAXN];
lint acc[MAXN];

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        int n, q;
        scanf("%d%d", &n, &q);
        for (int i = 1; i <= n; i++)
            scanf("%d", &v[i]);
        sort(v + 1, v + n + 1);
        for (int i = 1; i <= n; i++)
            acc[i] = acc[i - 1] + v[i];
        while (q--) {
            int k;
            scanf("%d", &k);
            int i = lower_bound(v + 1, v + n + 1, k) - v;
            int l = 1, r = i;
            while (l < r) {
                int mid = (l + r) / 2;
                lint needs = k * lint(i - mid) - (acc[i - 1] - acc[mid - 1]);
                if (needs > mid - 1) l = mid + 1;
                else r = mid;
            }
            printf("%d\n", n - l + 1);
        }
    }        
    return 0;
}
