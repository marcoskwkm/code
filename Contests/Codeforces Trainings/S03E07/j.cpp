#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10, MAXQ = (int)5e5 + 10;

// Single update range query Segtree
struct SegmentTree {
    struct Node {
        lint sum, best_l, best_r, best;
        Node() : sum(0), best_l(0), best_r(0), best(0) {}
        Node(lint s, lint l, lint r, lint b) : sum(s), best_l(l), best_r(r), best(b) {}

        // Merge two nodes
        Node operator+(const Node &that) {
            return Node(
                sum + that.sum,
                max(best_l, sum + that.best_l),
                max(that.best_r, best_r + that.sum),
                max(best_r + that.best_l, max(best, that.best)));
        }
    };

    vector<Node> tree;
    int n;

    SegmentTree(const vector<lint> &v) : n(v.size()) {
        tree.resize(4*n);
        build(0, 0, n - 1, v);
    }

    Node build(int i, int l, int r, const vector<lint> &v) {
        if (l == r) return tree[i] = Node(v[l], v[l], v[l], v[l]);
        int L = 2*i + 1, R = 2*i + 2, mid = (l + r) / 2;
        return tree[i] = build(L, l, mid, v) + build(R, mid + 1, r, v);
    }

    Node update(int i, int l, int r, int x, lint val) {
        if (x < l || x > r) return tree[i];
        if (l == r) return tree[i] = Node(val, val, val, val);
        int L = 2*i + 1, R = 2*i + 2, mid = (l + r) / 2;
        return tree[i] = update(L, l, mid, x, val) + update(R, mid + 1, r, x, val);            
    }
    Node update(int x, lint val) { return update(0, 0, n - 1, x, val); }

    Node query(int i, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return Node(0, -LINF, -LINF, -LINF);
        if (ql <= l && r <= qr) return tree[i];
        int L = 2*i + 1, R = 2*i + 2, mid = (l + r) / 2;
        return query(L, l, mid, ql, qr) + query(R, mid + 1, r, ql, qr);
    }
    Node query(int l, int r) { return query(0, 0, n - 1, l, r); }
};

/* A directed graph */
struct Graph {
    int V;
    vector<vector<int>> adj;
    
    Graph(int _V) : V(_V) {
        adj.resize(V);
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
    }
};

struct LCA {
    static const int LOG = 20;
    vector<int> up[LOG];
    vector<int> depth;

    const Graph &g;

    LCA(const Graph &_g, int root) : g(_g) {
        for (int i = 0; i < LOG; i++)
            up[i].resize(g.V);
        depth.resize(g.V);
        dfs(root, root, 0);
        for (int e = 1; e < LOG; e++)
            for (int v = 0; v < g.V; v++)
                up[e][v] = up[e - 1][up[e - 1][v]];
    }

    void dfs(int v, int prv, int d) {
        depth[v] = d;
        up[0][v] = prv;
        for (int nxt: g.adj[v])
            if (nxt != prv)
                dfs(nxt, v, d + 1);
    }

    int lca(int u, int v) {
        if (depth[u] > depth[v]) swap(u, v);
        for (int i = LOG - 1; i >= 0; i--)
            if (depth[up[i][v]] > depth[u])
                v = up[i][v];
        if (depth[v] > depth[u]) v = up[0][v];
        if (u == v) return u;
        for (int i = LOG - 1; i >= 0; i--)
            if (up[i][u] != up[i][v])
                u = up[i][u], v = up[i][v];
        return up[0][v];
    }
};    

lint val[MAXN];

vector<SegmentTree::Node> query[MAXQ];
vector<pii> half_query[MAXN];
int idx[MAXN];
int up[20][MAXN];

void dfs(const Graph &g, int v, int cnt, int prv, SegmentTree &tree) {
    idx[v] = cnt;
    tree.update(idx[v], val[v]);
    for (pii q: half_query[v]) {
        if (q.first < 0)
            query[q.second].push_back(tree.query(idx[-q.first] + 1, idx[v]));
        else
            query[q.second].push_back(tree.query(idx[q.first], idx[v]));
        // debug("(%d, %d): %lld, %lld, %lld, %lld\n",
        //       q.first, v,
        //       query[q.second].back().sum,
        //       query[q.second].back().best_l,
        //       query[q.second].back().best_r,
        //       query[q.second].back().best);
    }
    for (int nxt: g.adj[v])
        if (nxt != prv)
            dfs(g, nxt, cnt + 1, v, tree);
}

int main() {
    int n;
    scanf("%d", &n);
    Graph g(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        g.add_edge(u, v);
        g.add_edge(v, u);
    }
    LCA lca(g, 1);
    for (int i = 1; i <= n; i++) scanf("%lld", &val[i]);
    int q;
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        int w = lca.lca(u, v);
        // debug("lca(%d, %d) = %d\n", u, v, w);
        if (u == w) swap(u, v);
        half_query[u].push_back(pii(w, i));
        // debug("%d ~ %d\n", w, u);
        if (v != w) {
            half_query[v].push_back(pii(-w, i));
            // debug("%d ~ %d\n", -w, v);
        }
    }
    SegmentTree tree(vector<lint>(n, 0));
    dfs(g, 1, 0, -1, tree);
    for (int i = 0; i < q; i++) {
        if (query[i].size() == 1) printf("%lld\n", query[i][0].best);
        else {
            swap(query[i][0].best_l, query[i][0].best_r);
            printf("%lld\n", (query[i][0] + query[i][1]).best);
        }
    }    
    return 0;
}
