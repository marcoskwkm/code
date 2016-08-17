#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 210, MAXM = 2010;

int adj[MAXN][MAXM];
int deg[MAXN];
int block_u, block_v;
bool foi[MAXN];

void dfs(int v) {
    foi[v] = 1;
    for (int i = 0; i < deg[v]; i++) {
        int nxt = adj[v][i];
        if (v == block_u && nxt == block_v) continue;
        if (!foi[nxt]) dfs(nxt);
    }
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<pii> edges;
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u][deg[u]++] = v;
        edges.push_back(pii(u, v));
    }

    int s, t;
    scanf("%d%d", &s, &t);

    bool has = 0;
    for (pii p: edges) {
        memset(foi, 0, sizeof(foi));
        tie(block_u, block_v) = p;
        dfs(s);
        if (!foi[t]) {
            has = 1;
            break;
        }
    }
    printf("%d\n", has ? 1 : 0);
    return 0;
}
