#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr, args)
#define readArray(v, n) for_each(v.begin(), v.begin() + n, [](auto &x) { cin >> x; })

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

template <class T, class C = vector<T>> inline void printArray(C v, int n = -1) {
    int cnt = 0;
    for (auto it = v.begin(); it != v.end() && cnt != n; it++, cnt++) {
        cout << *it << (next(it) == v.end() || cnt + 1 == n ? '\n' : ' ');
    }
}

template <class T> struct SegmentTree {
    struct Node {
        T val;
        Node(T v = 0) : val(v) {}

        // Merge two nodes
        Node operator+(const Node &that) { return Node(max(val, that.val)); }
    };
    // Neutral element
    const Node ID = Node(-LINF);

    vector<Node> tree;
    int n;

    SegmentTree() {}
    SegmentTree(const vector<T> &v) { initialize(v); }

    void initialize(const vector<T> &v) {
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

    Node update(int i, int l, int r, int x, T val) {
        if (x < l || x > r)
            return tree[i];
        if (l == r)
            return tree[i] = Node(val);
        int L = 2 * i + 1, R = 2 * i + 2, mid = (l + r) / 2;
        return tree[i] = update(L, l, mid, x, val) + update(R, mid + 1, r, x, val);
    }
    Node update(int x, T val) { return update(0, 0, n - 1, x, val); }

    Node query(int i, int l, int r, int ql, int qr) {
        if (qr < l || r < ql)
            return ID;
        if (ql <= l && r <= qr)
            return tree[i];
        int L = 2 * i + 1, R = 2 * i + 2, mid = (l + r) / 2;
        return query(L, l, mid, ql, qr) + query(R, mid + 1, r, ql, qr);
    }
    T query(int l, int r) { return query(0, 0, n - 1, l, r).val; }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> h(n);
    vector<lint> b(n);
    readArray(h, n);
    readArray(b, n);
    vector<int> nxt_smaller(n);
    stack<int> st;

    for (int i = 0; i < n; i++) {
        while (!st.empty() && h[st.top()] > h[i]) {
            nxt_smaller[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
    while (!st.empty()) {
        nxt_smaller[st.top()] = n;
        st.pop();
    }

    vector<lint> blank(n + 1, 0);
    SegmentTree<lint> seg(blank);

    vector<lint> dp(n + 1);
    dp[n] = 0;
    for (int i = n - 1; i >= 0; i--) {
        dp[i] = b[i] + seg.query(i + 1, nxt_smaller[i]);
        if (nxt_smaller[i] < n) {
            dp[i] = max(dp[i], dp[nxt_smaller[i]]);
        }
        seg.update(i, dp[i]);
    }
    cout << dp[0] << endl;
    return 0;
}
