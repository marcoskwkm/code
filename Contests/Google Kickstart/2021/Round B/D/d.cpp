#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;
typedef tuple<int, int, int, lint> tiiil;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

lint _gcd(lint a, lint b) { return b ? _gcd(b, a % b) : a; }

// Single update range query segtree
template<class T> struct SegmentTree {
    // It should be enough to change only this struct for most use cases.
    struct Node {
        T gcd;
        Node(T v = 0) : gcd(v) {}

        // Merge two nodes
        Node operator+(const Node &that) {
            return Node(_gcd(gcd, that.gcd));
        }
    };
    // Neutral element
    const Node ID = Node(0);

    vector<Node> tree;
    int n;

    SegmentTree() {}
    SegmentTree(const vector<T> &v) { init(v); }

    void init(const vector<T> &v) {
        n = v.size();
        tree.resize(4 * n);
        for (auto &node: tree) {
            node.gcd = 0;
        }
    }

    Node update(int i, int l, int r, int x, T val) {
        if (x < l || x > r) return tree[i];
        if (l == r) return tree[i] = Node(val);
        int L = 2*i + 1, R = 2*i + 2, mid = (l + r) / 2;
        return tree[i] = update(L, l, mid, x, val) + update(R, mid + 1, r, x, val);
    }
    Node update(int x, T val) { return update(0, 0, n - 1, x, val); }

    Node query(int i, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return ID;
        if (ql <= l && r <= qr) return tree[i];
        int L = 2*i + 1, R = 2*i + 2, mid = (l + r) / 2;
        return query(L, l, mid, ql, qr) + query(R, mid + 1, r, ql, qr);
    }
    T query(int l, int r) { return query(0, 0, n - 1, l, r).gcd; }
};

// Directed weighted graph
template<class WTYPE> struct WeightedGraph {
    int V;
    vector<vector<pair<int, WTYPE>>> adj;

    WeightedGraph(int _V) : V(_V) { adj.resize(V); }

    void add_edge(int u, int v, WTYPE w) {
        adj[u].push_back(make_pair(v, w));
    }
};

// DataStructure must implement:
//   Empty constructor
//   init(vector with initial values)
//   query(l, r)
//   update(pos, val) or update(l, r, val)
template<class DataStructure> struct HeavyLight {
    DataStructure tree;
    vector<lint> heavy, parent, depth, value, root, pos;
    int n;

    int dfs(const WeightedGraph<lint> &g, int v) {
        int hi = 0, ret = 1;
        for (pii edge: g.adj[v]) {
            int nxt, cst;
            tie(nxt, cst) = edge;
            if (nxt == parent[v]) continue;
            parent[nxt] = v;
            value[nxt] = cst;
            depth[nxt] = depth[v] + 1;
            int got = dfs(g, nxt);
            if (got > hi) {
                hi = got;
                heavy[v] = nxt;
            }
            ret += got;
        }
        return ret;
    }

    HeavyLight(const WeightedGraph<lint> &g, int s) : n(g.V) {
        heavy = vector<lint>(n, -1);
        parent = depth = value = root = pos = vector<lint>(n);
        parent[s] = -1;
        dfs(g, s);
        vector<lint> tree_val(n);
        int cur = 0;
        for (int v = 0; v < n; v++) {
            if (parent[v] == -1 || heavy[parent[v]] != v) {
                for (int j = v; j != -1; j = heavy[j]) {
                    root[j] = v, pos[j] = cur++;
                    tree_val[pos[j]] = value[j];
                }
            }
        }
        tree.init(tree_val);
    }

    lint query(int u, int v) {
        lint ret = 0;
        for (; root[u] != root[v]; v = parent[root[v]]) {
            if (u == -1 || v == -1) abort();
            if (depth[root[u]] > depth[root[v]]) swap(u, v);
            ret = _gcd(ret, tree.query(pos[root[v]], pos[v]));
        }
        if (depth[u] > depth[v]) swap(u, v);
        if (u != v) ret = _gcd(ret, tree.query(pos[u] + 1, pos[v]));
        return ret;
    }

    // Single update
    void update(int v, lint val) { tree.update(pos[v], val); }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<tiiil> edges;
    WeightedGraph<lint> g(n);
    for (int i = 1; i < n; i++) {
        int u, v, l;
        lint a;
        scanf("%d%d%d%lld", &u, &v, &l, &a);
        edges.push_back(tiiil(u - 1, v - 1, l, a));
        g.add_edge(u - 1, v - 1, 0);
        g.add_edge(v - 1, u - 1, 0);
    }
    HeavyLight<SegmentTree<lint>> hld(g, 0);

    vector<tiii> queries;
    for (int i = 0; i < q; i++) {
        int c, w;
        scanf("%d%d", &c, &w);
        queries.push_back(tiii(c - 1, w, i));
    }

    sort(queries.begin(), queries.end(), [](tiii a, tiii b) {
        return get<1>(a) < get<1>(b);
    });
    sort(edges.begin(), edges.end(), [](tiiil a, tiiil b) {
        return get<2>(a) < get<2>(b);
    });

    vector<lint> ans(queries.size());
    size_t cur = 0;
    for (tiii query: queries) {
        // debug("query: %d %d (%d)\n", get<0>(query) + 1, get<1>(query), get<2>(query));
        while (cur < edges.size() && get<2>(edges[cur]) <= get<1>(query)) {
            int u = get<0>(edges[cur]), v = get<1>(edges[cur]);
            lint a = get<3>(edges[cur]);
            // debug("adding (%d, %d) (%lld)\n", u + 1, v + 1, a);
            if (hld.depth[u] < hld.depth[v]) {
                hld.update(v, a);
            } else {
                hld.update(u, a);
            }
            cur++;
        }

        lint gcd = hld.query(0, get<0>(query));
        ans[get<2>(query)] = gcd;
        // debug("answer: %lld\n", gcd);
    }

    for (lint sol: ans) {
        printf(" %lld", sol);
    }
    printf("\n");
}

int main() {
    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        printf("Case #%d:", t);
        solve();
    }
    return 0;
}
