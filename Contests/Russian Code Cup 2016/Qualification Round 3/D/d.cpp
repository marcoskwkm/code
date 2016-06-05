#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;

vector<int> adj[MAXN];

int parent[MAXN], heavy[MAXN], hld_pos[MAXN], depth[MAXN], root[MAXN];
int value[MAXN];

int tree[4*MAXN];

void tree_update(int i, int l, int r, int pos, int val) {
    if (l > pos || r < pos) return;
    if (l == r) {
        tree[i] = val;
        value[l] = val;
        return;
    }
    int L = 2*i + 1, R = 2*i + 2, mid = (l + r)/2;
    tree_update(L, l, mid, pos, val); tree_update(R, mid + 1, r, pos, val);
    tree[i] = tree[L] + tree[R];
}

int tree_query(int i, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return tree[i];
    if (ql > r || qr < l) return 0;
    int L = 2*i + 1, R = 2*i + 2, mid = (l + r)/2;
    return tree_query(L, l, mid, ql, qr) + tree_query(R, mid + 1, r, ql, qr);
}

pii hld_query(int u, int v, int n) {
    int ret = 0;
    for (; root[u] != root[v]; v = parent[root[v]]) {
        if (depth[root[u]] > depth[root[v]]) swap(u, v);
        ret += tree_query(0, 0, n - 1, hld_pos[root[v]], hld_pos[v]);
    }
    if (depth[u] > depth[v]) swap(u, v);
    if (u != v) ret += tree_query(0, 0, n - 1, hld_pos[u] + 1, hld_pos[v]);
    return pii(ret, u);
}

void hld_update(int pos, int val, int n) {
    tree_update(0, 0, n - 1, hld_pos[pos], val);
}

int hld_dfs(int v) {
    int hi = 0, ret = 1;
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

void hld_preprocess(int n) {
    memset(heavy, -1, sizeof(heavy));
    parent[1] = -1; depth[1] = 0;
    hld_dfs(1);
    int cur = 0;
    for (int v = 1; v <= n; v++)
        if (parent[v] == -1 || heavy[parent[v]] != v)
            for (int u = v; u != -1; u = heavy[u])
                root[u] = v, hld_pos[u] = cur++;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int v = 2; v <= n; v++) {
        int p;
        scanf("%d", &p);
        adj[v].push_back(p);
        adj[p].push_back(v);
    }
    hld_preprocess(n);
    int q;
    for (scanf("%d", &q); q--;) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int u, v;
            scanf("%d%d", &u, &v);
            pii got = hld_query(u, v, n);
            int dist = depth[u] + depth[v] - 2*depth[got.second];
            printf("%d\n", dist - got.first);
        }
        else {
            int v;
            scanf("%d", &v);
            hld_update(v, 1, n);
        }
    }    
    return 0;
}
