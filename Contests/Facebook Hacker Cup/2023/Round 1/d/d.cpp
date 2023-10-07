#ifdef CLANG
#include "stdcpp.h"
#endif
#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr, args)
#define read_array(v, n) for_each(v.begin(), v.begin() + n, [](auto &x) { cin >> x; })

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const lint MOD = (int)1e9 + 7;

template<class Fun> class y_combinator_result {
    Fun fun_;

  public:
    template<class T> explicit y_combinator_result(T &&fun) : fun_(forward<T>(fun)) {}

    template<class... Args> decltype(auto) operator()(Args &&...args) {
        return fun_(ref(*this), forward<Args>(args)...);
    }
};

template<class Fun> decltype(auto) y_combinator(Fun &&fun) {
    return y_combinator_result<decay_t<Fun>>(forward<Fun>(fun));
}

template<class T> vector<T> make_vector(size_t size, T initialValue) {
    return vector<T>(size, initialValue);
}

template<class T, class... Args> auto make_vector(size_t head, Args &&...rem) {
    auto inner = make_vector<T>(rem...);
    return vector<decltype(inner)>(head, inner);
}

template<class T, class C = vector<T>> inline void print_array(C v, int n = -1) {
    int cnt = 0;
    for (auto it = v.begin(); it != v.end() && cnt != n; it++, cnt++) {
        cout << *it << (next(it) == v.end() || cnt + 1 == n ? "" : " ");
    }
    cout << '\n';
}

template<class T = int> inline T read() {
    T x;
    cin >> x;
    return x;
}

// Range update range query segtree
template<class T> struct SegmentTree {
    struct Node {
        lint lazy;
        lint lo, hi;
        int il, ih;

        Node(lint x = 0, int i = 0) : lo(x % MOD), hi(x % MOD), il(i), ih(i), lazy(0) {}
        Node(lint l, lint h, int _il, int _ih) : lo(l), hi(h), il(_il), ih(_ih), lazy(0) {}

        // Merge two nodes
        Node operator+(const Node &that) {
            pll lop = min(pll(lo, il), pll(that.lo, that.il));
            pll hip = max(pll(hi, -ih), pll(that.hi, -that.ih));
            return Node(lop.first, hip.first, lop.second, -hip.second);
        }
    };
    // Neutral element
    const Node ID = Node(LINF, -LINF, 0, 0);

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
        if (l == r) return tree[i] = Node(v[l], l);
        int L = 2*i + 1, R = 2*i + 2, mid = (l + r) / 2;
        return tree[i] = build(L, l, mid, v) + build(R, mid + 1, r, v);
    }

    // Apply lazy updates to a node
    void refresh(int i, int l, int r) {
        tree[i].lazy %= 2;

        if (tree[i].lazy) {
            swap(tree[i].lo, tree[i].hi);
            swap(tree[i].il, tree[i].ih);
            tree[i].lo = MOD - tree[i].lo;
            tree[i].hi = MOD - tree[i].hi;
        }

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
    T query(int ql, int qr) { return query(0, 0, n - 1, ql, qr).ih; }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        int N;
        cin >> N;

        vector<lint> A(N);
        read_array(A, N);

        SegmentTree<lint> tree;
        tree.init(A);

        int Q;
        lint ans = 0;
        for (cin >> Q; Q--;) {
            int l, r;
            cin >> l >> r;
            tree.update(l - 1, r - 1, 1);
            // auto nd = tree.query(0, 0, N - 1, l - 1, r - 1);
            // debug("max = %lld, idx = %d\n", nd.hi, nd.ih);
            ans += tree.query(0, N - 1) + 1;
        }

        printf("Case #%d: %lld\n", t, ans);
    }

    return 0;
}
