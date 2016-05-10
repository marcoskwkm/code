#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)2e5 + 10;

vector<int> adj[MAXN];
int val[MAXN];

int parent[MAXN], heavy[MAXN], root[MAXN], depth[MAXN];
int hld_pos[MAXN];

int hld_dfs(int v) {
    int ret = 1, hi = 0;
    for (int nxt: adj[v]) {
        if (nxt == parent[v]) continue;
        parent[nxt] = v;
        depth[nxt] = depth[v] + 1;
        int got = hld_dfs(nxt);
        if (got > hi) {
            hi = got;
            heavy[v] = nxt;
        }
        ret += got;
    }
    return ret;
}

void hld_preprocess(int s, int n) {
    memset(heavy, -1, sizeof(heavy));
    parent[s] = -1;
    depth[s] = 0;
    hld_dfs(s);
    int cur = 0;
    for (int v = 1; v <= n; v++) {
        if (parent[v] == -1 || heavy[parent[v]] != v) {
            for (int u = v; u != -1; u = heavy[u]) {
                root[u] = v;
                hld_pos[u] = cur++;
            }
        }
    }
}

int tree[2][4*MAXN];

void tree_update(int k, int i, int l, int r, int pos, int value) {
    if (pos < l || pos > r) return;
    if (l == r) {
        tree[k][i] += value;
        return;
    }
    int L = 2*i + 1, R = 2*i + 2, mid = (l + r)/2;
    tree_update(k, L, l, mid, pos, value); tree_update(k, R, mid + 1, r, pos, value);
    tree[k][i] = tree[k][L] + tree[k][R];
}

int tree_query(int k, int i, int l, int r, int ql, int qr) {
    if (ql > r || qr < l) return 0;
    if (ql <= l && r <= qr) return tree[k][i];
    int L = 2*i + 1, R = 2*i + 2, mid = (l + r)/2;
    return tree_query(k, L, l, mid, ql, qr) + tree_query(k, R, mid + 1, r, ql, qr);
}

int hld_query(int k, int v, int n) {
    int ret = 0;
    while (v != -1) {
        ret += tree_query(k, 0, 0, n - 1, hld_pos[root[v]], hld_pos[v]);
        v = parent[root[v]];
    }
    return ret;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int v = 1; v <= n; v++)
        scanf("%d", &val[v]);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    hld_preprocess(1, n);
    for (int i = 0; i < m; i++) {
        int op, x, value;
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d%d", &x, &value);
            int parity = depth[x] & 1;
            tree_update(parity, 0, 0, n-1, hld_pos[x], value);
        }
        else {
            scanf("%d", &x);
            int parity = depth[x] & 1;
            printf("%d\n", val[x] + hld_query(parity, x, n) - hld_query(parity ^ 1, x, n));
        }
    }        
    return 0;
}
