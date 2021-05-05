// It should be enough to change only this struct for most applications
struct Node {
    lint val;

    Node() {}
    Node(lint v) : val(v) {}

    // Merge two nodes
    Node operator+(const Node &that) { return Node(max(val, that.val)); }

    // Apply update
    Node update(lint upd) {
        val = upd;
        return *this;
    }

    // Neutral element
    static Node ID() { return Node(-LINF); }
};

// Single update range query segtree
template<class N, class U> struct SegmentTree {
    vector<N> tree;
    int n;

    SegmentTree() {}
    SegmentTree(const vector<N> &v) { init(v); }

    void init(const vector<N> &v) {
        n = v.size();
        tree.resize(4 * n);
        build(0, 0, n - 1, v);
    }

    N build(int i, int l, int r, const vector<N> &v) {
        if (l == r)
            return tree[i] = v[l];
        int L = 2 * i + 1, R = 2 * i + 2, mid = (l + r) / 2;
        return tree[i] = build(L, l, mid, v) + build(R, mid + 1, r, v);
    }

    N update(int i, int l, int r, int x, U val) {
        if (x < l || x > r)
            return tree[i];
        if (l == r)
            return tree[i].update(val);
        int L = 2 * i + 1, R = 2 * i + 2, mid = (l + r) / 2;
        return tree[i] = update(L, l, mid, x, val) + update(R, mid + 1, r, x, val);
    }
    N update(int x, U val) { return update(0, 0, n - 1, x, val); }

    N query(int i, int l, int r, int ql, int qr) {
        if (qr < l || r < ql)
            return N::ID();
        if (ql <= l && r <= qr)
            return tree[i];
        int L = 2 * i + 1, R = 2 * i + 2, mid = (l + r) / 2;
        return query(L, l, mid, ql, qr) + query(R, mid + 1, r, ql, qr);
    }
    N query(int l, int r) { return query(0, 0, n - 1, l, r); }
};
