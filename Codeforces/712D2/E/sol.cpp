#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr, args)
#define readIntArray(v, n) for_each(v.begin(), v.begin() + n, [](int &x) { scanf("%d", &x); })
#define readLintArray(v, n) for_each(v.begin(), v.begin() + n, [](lint &x) { scanf("%lld", &x); })

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

// Range update range query segtree
template <class T> struct SegmentTree {
    struct Node {
        T val, lazy;

        Node(lint _val = 0) : val(_val), lazy(0) {}

        // Merge two nodes
        Node operator+(const Node &that) { return Node(min(val, that.val)); }
    };
    // Neutral element
    const Node ID = Node(LINF);

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
        if (l == r)
            return tree[i] = Node(v[l]);
        int L = 2 * i + 1, R = 2 * i + 2, mid = (l + r) / 2;
        return tree[i] = build(L, l, mid, v) + build(R, mid + 1, r, v);
    }

    // Apply lazy updates to a node
    void refresh(int i, int l, int r) {
        tree[i].val += tree[i].lazy;
        if (l < r) {
            tree[2 * i + 1].lazy += tree[i].lazy;
            tree[2 * i + 2].lazy += tree[i].lazy;
        }
        tree[i].lazy = 0;
    }

    Node update(int i, int l, int r, int ql, int qr, T val) {
        refresh(i, l, r);
        if (r < ql || qr < l)
            return tree[i];
        if (ql <= l && r <= qr) {
            tree[i].lazy += val;
            refresh(i, l, r);
            return tree[i];
        }
        int L = 2 * i + 1, R = 2 * i + 2, mid = (l + r) / 2;
        return tree[i] = update(L, l, mid, ql, qr, val) + update(R, mid + 1, r, ql, qr, val);
    }
    void update(int ql, int qr, T val) { update(0, 0, n - 1, ql, qr, val); }

    Node query(int i, int l, int r, int ql, int qr) {
        refresh(i, l, r);
        if (r < ql || qr < l)
            return ID;
        if (ql <= l && r <= qr)
            return tree[i];
        int L = 2 * i + 1, R = 2 * i + 2, mid = (l + r) / 2;
        return query(L, l, mid, ql, qr) + query(R, mid + 1, r, ql, qr);
    }
    T query(int ql, int qr) { return query(0, 0, n - 1, ql, qr).val; }
};

int main() {
    int n;
    cin >> n;
    vector<pii> cities(n);
    for (int i = 0; i < n; i++) {
        int a, c;
        scanf("%d%d", &a, &c);
        cities[i] = pii(a, c);
    }

    sort(cities.begin(), cities.end());
    vector<lint> initial_state(n, 0);
    SegmentTree<lint> seg_a(initial_state), seg_c(initial_state);

    vector<lint> dp(n);
    dp[n - 1] = cities[n - 1].second;
    seg_a.update(n - 1, n - 1, dp[n - 1] + cities[n - 1].first);
    seg_c.update(n - 1, n - 1, dp[n - 1]);

    for (int i = n - 2; i >= 0; i--) {
        int upper_idx = max<int>(i + 1, lower_bound(cities.begin(), cities.end(),
                                                    pii(cities[i].first + cities[i].second, 0)) -
                                            cities.begin());
        lint val = LINF;
        if (upper_idx != n) {
            val = min(val, seg_a.query(upper_idx, n - 1) - cities[i].first);
        }
        if (upper_idx - 1 > i) {
            val = min(val, seg_c.query(i + 1, upper_idx - 1) + cities[i].second);
        }
        dp[i] = val;
        seg_a.update(i, i, dp[i] + cities[i].first);
        seg_c.update(i, i, dp[i]);
        seg_a.update(i + 1, n - 1, cities[i].second);
        seg_c.update(i + 1, n - 1, cities[i].second);
    }

    printf("%lld\n", dp[0]);
    return 0;
}
