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
const string IMPOSSIBLE = "IMPOSSIBLE";

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
        T val, cnt, lazy;

        Node(lint _val = 0, lint _cnt = 1) : val(_val), cnt(_cnt), lazy(0) {}

        // Merge two nodes
        Node operator+(const Node &that) {
            if (val > that.val) {
                return *this;
            } else if (that.val > val) {
                return that;
            }

            return Node(val, cnt + that.cnt);
        }
    };
    // Neutral element
    const Node ID = Node(0, 0);

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
    Node query(int ql, int qr) { return query(0, 0, n - 1, ql, qr); }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        printf("Case #%d: ", t);

        int N, C;
        cin >> N >> C;

        vector<int> A(C), B(C);
        for (int i = 0; i < C; i++) {
            cin >> A[i] >> B[i];
        }

        vector<int> color(2 * N);
        for (int i = 0; i < N; i++) {
            color[i] = color[N + i] = read() - 1;
        }

        vector<vector<int>> appearances(C);

        for (int i = 0; i < 2 * N; i++) {
            appearances[color[i]].push_back(i);
        }

        SegmentTree<lint> tree(vector<lint>(2 * N));
        vector<int> idx(C, 0);

        auto get_intervals = [&](int c, int i, int pos) {
            vector<pii> intervals;

            if (i == (int)appearances[c].size()) {
                intervals.push_back({0, 2 * N - 1});
                return intervals;
            }

            if (appearances[c][i] > pos) {
                intervals.push_back({0, appearances[c][i] - 1});
            }

            if (B[c] > 0) {
                if (A[c] + i >= (int)appearances[c].size()) {
                    return intervals;
                }
                int l = appearances[c][max(1, A[c]) - 1 + i];
                int r = B[c] + i >= (int)appearances[c].size() ? 2 * N : appearances[c][B[c] + i];
                intervals.push_back({l, r - 1});
            }

            return intervals;
        };

        for (int c = 0; c < C; c++) {
            auto intervals = get_intervals(c, 0, 0);
            for (auto &[l, r]: intervals) {
                tree.update(l, r, 1);
            }
        }

        lint ans = 0;

        for (int i = 0; i < N; i++) {
            auto q = tree.query(i + 1, i + N - 2);

            if (q.val == C) {
                ans += q.cnt;
            }

            auto pre_intervals = get_intervals(color[i], idx[color[i]], i);
            for (auto &[l, r]: pre_intervals) {
                tree.update(l, r, -1);
            }

            idx[color[i]]++;

            auto pos_intervals = get_intervals(color[i], idx[color[i]], i + 1);
            for (auto &[l, r]: pos_intervals) {
                tree.update(l, r, 1);
            }
        }

        printf("%lld\n", ans);
    }

    return 0;
}
