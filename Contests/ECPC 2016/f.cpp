#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;

int n, m, C;
lint r[MAXN], c[MAXN], p[MAXN];
vector<int> diag[2 * MAXN];

int solve(int i) {
    sort(diag[i].begin(), diag[i].end(), [](int a, int b) {
        if (c[a] + p[a]*p[a] == c[b] + p[b]*p[b])
            return c[a] < c[b];
        return c[a] + p[a]*p[a] < c[b] + p[b]*p[b];
    });
    int ret = 0;
    lint lim = -LINF;
    for (int x: diag[i]) {
        if (c[x] < lim + p[x]*p[x]) continue;
        ret++;
        lim = c[x] + p[x]*p[x] + C - 1;
    }
    return ret;
}    

int main() {
    #ifndef HOME
    freopen("bishops.in", "r", stdin);
    #endif

    int t;
    for (scanf("%d", &t); t--;) {
        scanf("%d%d%d", &n, &m, &C);
        for (int i = 0; i < m; i++) {
            int rr, cc, pp;
            scanf("%d%d%d", &rr, &cc, &pp);
            r[i] = rr, c[i] = cc, p[i] = pp;
        }
        int ans = 0;
        for (int i = 0; i <= 2*n; i++)
            diag[i].clear();
        for (int i = 0; i < m; i++)
            diag[r[i] + c[i]].push_back(i);
        for (int i = 0; i <= 2*n; i++)
            ans = max(ans, solve(i));

        for (int i = 0; i <= 2*n; i++)
            diag[i].clear();
        for (int i = 0; i < m; i++)
            diag[r[i] - c[i] + n].push_back(i);
        for (int i = 0; i <= 2*n; i++)
            ans = max(ans, solve(i));
        printf("%d\n", ans);
    }        
    return 0;
}
