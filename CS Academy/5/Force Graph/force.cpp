#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;

lint fx[MAXN], fy[MAXN];
lint x[MAXN], y[MAXN];

int main() {
    int n, m, f1, f2;
    scanf("%d%d%d%d", &n, &m, &f1, &f2);
    vector<pii> adj;
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj.push_back(pii(u, v));
    }
    lint sx = 0, sy = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%lld%lld", &x[i], &y[i]);
        sx += x[i];
        sy += y[i];
    }
    for (int i = 1; i <= n; i++) {
        fx[i] = f2*(n*x[i] - sx);
        fy[i] = f2*(n*y[i] - sy);
    }
    for (pii p: adj) {
        int u = p.first, v = p.second;
        fx[u] += (f1 - f2)*(x[u] - x[v]);
        fy[u] += (f1 - f2)*(y[u] - y[v]);
        fx[v] += (f1 - f2)*(x[v] - x[u]);
        fy[v] += (f1 - f2)*(y[v] - y[u]);
    }
    for (int i = 1; i <= n; i++)
        printf("%lld %lld\n", fx[i], fy[i]);
    return 0;
}
