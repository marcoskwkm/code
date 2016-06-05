// Max segment tree 

int tree[4*MAXN];
int tree_val[MAXN];
int value[MAXN]; // initial value of node [i]

void tree_build(int i, int l, int r) {
    if (l == r) {
        tree[i] = tree_val[l];
        return;
    }
    int L = 2*i + 1, R = 2*i + 2, mid = (l + r)/2;
    tree_build(L, l, mid); tree_build(R, mid + 1, r);
    tree[i] = max(tree[L], tree[R]);
}

void tree_update(int i, int l, int r, int pos, int val) {
    if (l > pos || r < pos) return;
    if (l == r) {
        tree[i] = val;
        return;
    }
    int L = 2*i + 1, R = 2*i + 2, mid = (l + r)/2;
    tree_update(L, l, mid, pos, val); tree_update(R, mid + 1, r, pos, val);
    tree[i] = max(tree[L], tree[R]);
}

int tree_query(int i, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return tree[i];
    if (ql > r || qr < l) return -INF;
    int L = 2*i + 1, R = 2*i + 2, mid = (l + r)/2;
    return max(tree_query(L, l, mid, ql, qr), tree_query(R, mid + 1, r, ql, qr));
}

int hld_dfs(int v) {
    int hi = 0, ret = 1;
    for (int i = 0; i < (int)adj[v].size(); i++) {
        int nxt = adj[v][i].first, cst = adj[v][i].second;        
        if (nxt == parent[v]) continue;
        parent[nxt] = v;
        value[nxt] = cst;
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
    parent[s] = -1; depth[s] = 0; value[s] = -INF;
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
    tree_build(0, 0, n-1);    
}

int hld_query(int u, int v, int n) {
    int ret = -INF;
    for (; root[u] != root[v]; v = parent[root[v]]) {
        if (depth[root[u]] > depth[root[v]]) swap(u, v);
        ret = max(ret, tree_query(0, 0, n-1, hld_pos[root[v]], hld_pos[v]));
    }
    if (depth[u] > depth[v]) swap(u, v);
    if (u != v) ret = max(ret, tree_query(0, 0, n - 1, hld_pos[u] + 1, hld_pos[v]));
    return ret;
}

inline void hld_update(int v, int val, int n) {
    tree_update(0, 0, n - 1, hld_pos[v], val);
}
