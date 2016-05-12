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
int init_value[MAXN];

struct SegmentTree {
    struct Data {
        int size;
        int total;
        int best_l, best, best_r;
        Data() {}
        Data(int t, int a, int b, int c, int s = 0) :
            size(s), total(t), best_l(a), best(b), best_r(c) {}        
    };

    typedef int D_TYPE; // data type
    
    struct Node {
        D_TYPE val;
        int lazy;
        bool flag;
        Node() { flag = 0; }
    };

    vector<Node> tree;
    int N;

    SegmentTree(int n) { N = n; tree.resize(4*n + 1); }

    inline D_TYPE merge(D_TYPE dl, D_TYPE dr) {
        D_TYPE ret(dl.total + dr.total, max(dl.best_l, dl.total + dr.best_l),
                   max(dl.best, dr.best), max(dr.best_r, dr.total + dl.best_r),
                   dl.size + dr.size);
        return ret;
    }

    void build(int i, int l, int r, int *v) {
        if (l == r) { tree[i].val = Data(v[l], v[l], v[l], v[l], 1); tree[i].flag = 0; }
        else {
            int L = 2*i + 1, R = 2*i + 2, mid = (l + r)/2;
            build(L, l, mid, v); build(R, mid + 1, r, v);
            tree[i].val = merge(tree[L].val, tree[R].val);
        }
    }
    
    void init(int *v) { build(0, 0, N - 1, v); }

    void refresh(int i) {
        // customize
        if (!tree[i].flag) return;
        tree[i].flag = 0;
        tree[i].val = tree[i].lazy;
        int L = 2*i + 1, R = 2*i + 2;
        if (L >= 4*N) return;
        tree[L].flag = tree[R].flag = 1;
        tree[L].lazy = tree[R].lazy = tree[i].lazy;
    }

    void _update(int i, int l, int r, int ql, int qr, int val) {
        refresh(i);
        if (r < ql || l > qr) return;
        if (ql <= l && r <= qr) {
            // customize
            tree[i].flag = 1;
            tree[i].lazy = val;
            refresh(i);
            return;
        }
        int L = 2*i + 1, R = 2*i + 2, mid = (l + r)/2;
        _update(L, l, mid, ql, qr, val);
        _update(R, mid + 1, r, ql, qr, val);
        tree[i].val = merge(tree[L].val, tree[R].val);
    }

    void update(int l, int r, int val) { _update(0, 0, N - 1, l, r, val); }

    D_TYPE _query(int i, int l, int r, int ql, int qr) {
        refresh(i);
        if (r < ql || l > qr) return -INF; // customize
        if (ql <= l && r <= qr) return tree[i].val;
        // customize
        int L = 2*i + 1, R = 2*i + 2, mid = (l + r)/2;
        D_TYPE dl = _query(L, l, mid, ql, qr);
        D_TYPE dr = _query(R, mid + 1, r, ql, qr);
        return merge(dl, dr);
    }

    D_TYPE query(int l, int r) { return _query(0, 0, N - 1, l, r); }
};


int parent[MAXN], heavy[MAXN], hld_pos[MAXN], depth[MAXN], root[MAXN];
int tree_init_value[MAXN];

void hld_preprocess(int n) {
    memset(heavy, -1, sizeof(heavy));
    parent[1] = -1; depth[1] = 0;
    hld_dfs(1);
    int cur = 0;
    for (int v = 1; v <= n; v++)
        if (parent[v] == -1 || heavy[parent[v]] != v)
            for (int u = v; u != -1; u = heavy[u])
                root[u] = v, hld_pos[u] = cur++;
    SegmentTree tree(4*n);
    for (int v = 1; v <= n; v++)
        tree_init_value[v] = hld_pos[v];
    tree.init(tree_init_value);
}

int main() {
    int n;
    scanf("%d", &n);
    for (int v = 1; v <= n; v++) scanf("%d", &init_value[v]);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    hld_preprocess(n);
    return 0;
}
