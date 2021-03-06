#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

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

    SegmentTree(const vector<int> &v) : n(v.size()) {
        tree.resize(4*n);
        build(0, 0, n - 1, v);
    }

    Node build(int i, int l, int r, const vector<int> &v) {
        if (l == r) return tree[i] = Node(v[l], v[l], v[l], v[l]);
        int L = 2*i + 1, R = 2*i + 2, mid = (l + r) / 2;
        return tree[i] = build(L, l, mid, v) + build(R, mid + 1, r, v);
    }

    Node update(int i, int l, int r, int x, int val) {
        if (x < l || x > r) return tree[i];
        if (l == r) return tree[i] = Node(val, val, val, val);
        int L = 2*i + 1, R = 2*i + 2, mid = (l + r) / 2;
        return tree[i] = update(L, l, mid, x, val) + update(R, mid + 1, r, x, val);            
    }
    Node update(int x, int val) { return update(0, 0, n - 1, x, val); }

    Node query(int i, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return Node(0, -LINF, -LINF, -LINF);
        if (ql <= l && r <= qr) return tree[i];
        int L = 2*i + 1, R = 2*i + 2, mid = (l + r) / 2;
        return query(L, l, mid, ql, qr) + query(R, mid + 1, r, ql, qr);
    }
    Node query(int l, int r) { return query(0, 0, n - 1, l, r); }
};    


int main() {
    int n;
    scanf("%d", &n);
    vector<int> v(n);
    for (int i = 0; i < n; i++)
        scanf("%d", &v[i]);
    int q;
    SegmentTree tree(v);
    for (scanf("%d", &q); q--;) {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%lld\n", tree.query(l - 1, r - 1).best);
    }        
    return 0;
}
