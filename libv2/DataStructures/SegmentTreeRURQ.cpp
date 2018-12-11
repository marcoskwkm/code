// Range update range query segtree
template<class T> struct SegmentTree {
    struct Node {
        T val, lazy;
        
        Node(lint _val = 0) : val(_val), lazy(0) {}

        // Merge two nodes
        Node operator+(const Node &that) {
            return Node(val + that.val);
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
        build(0, 0, n - 1, v);
    }

    Node build(int i, int l, int r, const vector<T> &v) {
        if (l == r) return tree[i] = Node(v[l]);
        int L = 2*i + 1, R = 2*i + 2, mid = (l + r) / 2;
        return tree[i] = build(L, l, mid, v) + build(R, mid + 1, r, v);
    }

    // Apply lazy updates to a node
    void refresh(int i, int l, int r) {
        tree[i].val += tree[i].lazy * (r - l + 1);
        if (l < r) {
            tree[2 * i + 1].lazy += tree[i].lazy;
            tree[2 * i + 2].lazy += tree[i].lazy;
        }
        tree[i].lazy = 0;
    }        

    Node update(int i, int l, int r, int ql, int qr, T val) {
        refresh(i, l, r);
        if (r < ql || qr < l) return tree[i];
        if (ql <= l && r <= qr) {
            tree[i].lazy += val;
            refresh(i, l, r);
            return tree[i];
        }
        int L = 2*i + 1, R = 2*i + 2, mid = (l + r) / 2;
        return tree[i] = update(L, l, mid, ql, qr, val) + update(R, mid + 1, r, ql, qr, val);            
    }
    void update(int ql, int qr, T val) { update(0, 0, n - 1, ql, qr, val); }

    Node query(int i, int l, int r, int ql, int qr) {
        refresh(i, l, r);
        if (r < ql || qr < l) return ID;
        if (ql <= l && r <= qr) return tree[i];
        int L = 2*i + 1, R = 2*i + 2, mid = (l + r) / 2;
        return query(L, l, mid, ql, qr) + query(R, mid + 1, r, ql, qr);
    }
    T query(int ql, int qr) { return query(0, 0, n - 1, ql, qr).val; }
};
