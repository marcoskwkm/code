// Single update range query segtree
template<class T> struct SegmentTree {
    // It should be enough to change only this struct for most use cases.
    struct Node {
        T sum, best_l, best_r, best;
        Node(T v = 0) : sum(v), best_l(v), best_r(v), best(v) {}
        Node(T s, T l, T r, T b) : sum(s), best_l(l), best_r(r), best(b) {}

        // Merge two nodes
        Node operator+(const Node &that) {
            return Node(
                sum + that.sum,
                max(best_l, sum + that.best_l),
                max(that.best_r, best_r + that.sum),
                max(best_r + that.best_l, max(best, that.best)));
        }
    };
    // Neutral element
    const Node ID = Node(0, -LINF, -LINF, -LINF);

    vector<Node> tree;
    int n;

    SegmentTree() {}
    SegmentTree(const vector<T> &v) { init(v); }
    
    void init(const vector<T> &v) : n(v.size()) {
        tree.resize(4 * n);
        build(0, 0, n - 1, v);
    }

    Node build(int i, int l, int r, const vector<T> &v) {
        if (l == r) return tree[i] = Node(v[l]);
        int L = 2*i + 1, R = 2*i + 2, mid = (l + r) / 2;
        return tree[i] = build(L, l, mid, v) + build(R, mid + 1, r, v);
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
    T query(int l, int r) { return query(0, 0, n - 1, l, r).best; }
};
