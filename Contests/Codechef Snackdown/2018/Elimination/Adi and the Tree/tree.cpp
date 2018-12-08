#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)2.5e5 + 10;

int tree[4*MAXN];
int tree_val[4*MAXN];
int tree_lazy[4*MAXN];
int value[MAXN]; // initial value of node [i]
int parent[MAXN];
int depth[MAXN], heavy[MAXN], root[MAXN], hld_pos[MAXN];

vector<int> adj[MAXN];

// void tree_build(int i, int l, int r) {
//     if (l == r) {
//         tree[i] = tree_val[l];
//         return;
//     }
//     int L = 2*i + 1, R = 2*i + 2, mid = (l + r)/2;
//     tree_build(L, l, mid); tree_build(R, mid + 1, r);
//     tree[i] = max(tree[L], tree[R]);
// }

void refresh(int i, int l, int r) {
    if (!tree_lazy[i]) return;
    tree[i] = r - l + 1 - tree[i];
    if (l < r) {
        tree_lazy[2 * i + 1] ^= 1;
        tree_lazy[2 * i + 2] ^= 1;
    }
    tree_lazy[i] = 0;
}

void tree_update(int i, int l, int r, int ql, int qr) {
    refresh(i, l, r);
    if (r < ql || qr < l) return;
    if (ql <= l && r <= qr) {
        tree_lazy[i] ^= 1;
        refresh(i, l, r);
        return;
    }
    int L = 2*i + 1, R = 2*i + 2, mid = (l + r)/2;
    tree_update(L, l, mid, ql, qr); tree_update(R, mid + 1, r, ql, qr);
    tree[i] = tree[L] + tree[R];
}

int tree_query(int i, int l, int r, int ql, int qr) {
    refresh(i, l, r);
    if (ql <= l && r <= qr) return tree[i];
    if (ql > r || qr < l) return 0;
    int L = 2*i + 1, R = 2*i + 2, mid = (l + r)/2;
    return tree_query(L, l, mid, ql, qr) + tree_query(R, mid + 1, r, ql, qr);
}

int hld_dfs(int v) {
    int hi = 0, ret = 1;
    // for (int i = 0; i < (int)adj[v].size(); i++) {
    //     int nxt = adj[v][i].first, cst = adj[v][i].second;
    for (int nxt: adj[v]) {
        if (nxt == parent[v]) continue;
        parent[nxt] = v;
        value[nxt] = 0;
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
    parent[s] = -1; depth[s] = 0; value[s] = 0;
    hld_dfs(s);
    int cur = 0;
    // 1-indexed
    for (int v = 1; v <= n; v++) {
        if (parent[v] == -1 || heavy[parent[v]] != v) {
            for (int j = v; j != -1; j = heavy[j]) {
                root[j] = v, hld_pos[j] = cur++;
                tree_val[hld_pos[j]] = value[j];
            }
        }
    }
    // tree_build(0, 0, n-1);    
}

int hld_query(int u, int v, int n) {
    // debug("query\n");
    int ret = 0;
    for (; root[u] != root[v]; v = parent[root[v]]) {
        if (depth[root[u]] > depth[root[v]]) swap(u, v);
        int got = tree_query(0, 0, n-1, hld_pos[root[v]], hld_pos[v]);
        // debug("%d - %d: %d\n", root[v], v, got);
        ret += got;
    }
    if (depth[u] > depth[v]) swap(u, v);
    if (u != v) {
        int got = tree_query(0, 0, n - 1, hld_pos[u] + 1, hld_pos[v]);
        // debug("'%d' - %d: %d\n", u, v, got);
        ret += got;
    }
    // debug("---\n");
    return ret;
}

void hld_update(int u, int v, int n) {
    for (; root[u] != root[v]; v = parent[root[v]]) {
        if (depth[root[u]] > depth[root[v]]) swap(u, v);
        tree_update(0, 0, n-1, hld_pos[root[v]], hld_pos[v]);
    }
    if (depth[u] > depth[v]) swap(u, v);
    if (u != v) tree_update(0, 0, n - 1, hld_pos[u] + 1, hld_pos[v]);
}

int main() {
    int n, m;
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    hld_preprocess(1, n);

    int ans = 0;
    for (cin >> m; m--;) {
        int u, v;
        scanf("%d%d", &u, &v);
        ans -= hld_query(u, v, n);
        hld_update(u, v, n);
        ans += hld_query(u, v, n);
        printf("%d\n", ans);
    }    
        
    return 0;
}
