#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 110;

vector<int> adj[MAXN];
bool seen[MAXN];
int siz[MAXN];

bool dfs(int v, int prv = -1) {
    seen[v] = 1;
    for (int nxt: adj[v]) {
        if (nxt == prv) continue;
        if (seen[nxt]) return 0;
        if (!dfs(nxt, v)) return 0;
        siz[v] += siz[nxt];
    }
    siz[v]++;
    return 1;
}

int grid[2 * MAXN][2 * MAXN];

void solve(int v, int dr, int dc, int k, int prv = -1) {
    for (int r = 0; r < 2 * siz[v] - 1; r++)
        for (int c = 0; c < 2 * siz[v] - 1; c++)
            grid[r + dr][c + dc] = k;
    int off = 1;
    for (int nxt: adj[v]) {
        if (nxt == prv) continue;
        solve(nxt, dr + off, dc + off, k ^ 1, v);
        off += 2 * siz[nxt];
    }
}        

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    if (!dfs(1)) {
        printf("-1\n");
        return 0;
    }
    for (int i = 1; i <= n; i++) {
        if (!seen[i]) {
            printf("-1\n");
            return 0;
        }
    }

    solve(1, 0, 0, 0);
    printf("%d %d\n", 2 * n - 1, 2 * n - 1);
    for (int r = 0; r < 2 * n - 1; r++) {
        for (int c = 0; c < 2 * n - 1; c++)
            printf("%d", grid[r][c]);
        printf("\n");
    }
    
    return 0;
}
