#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;

int best[MAXN];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<pii> edges;
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u < v) swap(u, v);
        edges.push_back(pii(u, v));
    }
    sort(edges.begin(), edges.end(), [](pii a, pii b) {
        if (a.second != b.second) return a.second > b.second;
        return a.first > b.first;
    });

    for (int v = 1; v <= n; v++)
        best[v] = 1;
    
    for (int i = 0; i < m; i++) {
        int u, v;
        tie(u, v) = edges[i];
        int nxtu = max(best[u], 1 + best[v]);
        int nxtv = max(best[v], 1 + best[u]);
        best[u] = nxtu;
        best[v] = nxtv;
    }

    for (int v = 1; v <= n; v++)
        printf("%d%c", best[v], v == n ? '\n' : ' ');
    
    return 0;
}
