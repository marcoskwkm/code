#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 110;

int d[MAXN][MAXN];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    memset(d, INF, sizeof(d));
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        d[u][v] = d[v][u] = 1;
    }
    for (int i = 1; i <= n; i++)
        d[i][i] = 0;
    for (int k = 1; k <= n; k++)
        for (int u = 1; u <= n; u++)
            for (int v = 1; v <= n; v++)
                d[u][v] = min(d[u][v], d[u][k] + d[k][v]);
    char ans = 'S';
    for (int u = 1; u <= n; u++)
        for (int v = 1; v <= n; v++)
            if (d[u][v] > 6)
                ans = 'N';
    printf("%c\n", ans);
    return 0;
}
