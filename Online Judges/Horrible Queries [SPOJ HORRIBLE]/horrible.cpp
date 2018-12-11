#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

// Range update range query segtree
template<class T> struct SegmentTree {
    static const int MAXN = (int)1e5 + 10;

    T val[4 * MAXN], lazy[4 * MAXN];

    int n;

    SegmentTree(const vector<T> &v) : n(v.size()) {
        build(0, 0, n - 1, v);
    }

    T build(int i, int l, int r, const vector<T> &v) {
        lazy[i] = 0;
        if (l == r) return val[i] = v[l];
        int L = 2 * i + 1, R = 2 * i + 2, mid = (l + r) / 2;
        return val[i] = build(L, l, mid, v) + build(R, mid + 1, r, v);
    }

    // Apply lazy updates to a node
    void refresh(int i, int l, int r) {
        val[i] += lazy[i] * (r - l + 1);
        if (l < r) {
            lazy[2 * i + 1] += lazy[i];
            lazy[2 * i + 2] += lazy[i];
        }
        lazy[i] = 0;
    }        

    T update(int i, int l, int r, int ql, int qr, T v) {
        refresh(i, l, r);
        if (r < ql || qr < l) return val[i];
        if (ql <= l && r <= qr) {
            lazy[i] += v;
            refresh(i, l, r);
            return val[i];
        }
        int L = 2 * i + 1, R = 2 * i + 2, mid = (l + r) / 2;
        return val[i] = update(L, l, mid, ql, qr, v) + update(R, mid + 1, r, ql, qr, v);            
    }

    T query(int i, int l, int r, int ql, int qr) {
        refresh(i, l, r);
        if (r < ql || qr < l) return 0; // Neutral element
        if (ql <= l && r <= qr) return val[i];
        int L = 2 * i + 1, R = 2 * i + 2, mid = (l + r) / 2;
        return query(L, l, mid, ql, qr) + query(R, mid + 1, r, ql, qr);
    }
};

int main() {
    int t;
    for (cin >> t; t--;) {
        int n, c;
        scanf("%d%d", &n, &c);
        SegmentTree<lint> tree(vector<lint>(n + 1, 0));
        while (c--) {
            int op;
            scanf("%d", &op);
            if (op == 0) {
                int l, r, v;
                scanf("%d%d%d", &l, &r, &v);
                tree.update(0, 0, n, l, r, v);
            }
            else {
                int l, r;
                scanf("%d%d", &l, &r);
                printf("%lld\n", tree.query(0, 0, n, l, r));
            }
        }
    }
    return 0;
}
