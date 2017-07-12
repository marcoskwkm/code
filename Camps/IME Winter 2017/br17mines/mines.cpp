#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;

// Single update range query segtree
struct SegmentTree {
    struct Node {
        int val;
        Node(int x = 0) { val = x; }
        // Merge two nodes
        Node operator+(const Node &that) {
            return Node(min(val, that.val));
        }
    };

    vector<Node> tree;
    int n;

    SegmentTree(const vector<int> &v) : n(v.size()) {
        tree.resize(4 * n);
        build(0, 0, n - 1, v);
    }

    Node build(int i, int l, int r, const vector<int> &v) {
        if (l == r) return tree[i] = Node(v[l]);
        int L = 2*i + 1, R = 2*i + 2, mid = (l + r) / 2;
        return tree[i] = build(L, l, mid, v) + build(R, mid + 1, r, v);
    }

    Node update(int i, int l, int r, int x, int val) {
        if (x < l || x > r) return tree[i];
        if (l == r) return tree[i] = Node(val);
        int L = 2*i + 1, R = 2*i + 2, mid = (l + r) / 2;
        return tree[i] = update(L, l, mid, x, val) + update(R, mid + 1, r, x, val);            
    }
    Node update(int x, int val) { return update(0, 0, n - 1, x, val); }

    Node query(int i, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return Node(INF);
        if (ql <= l && r <= qr) return tree[i];
        int L = 2*i + 1, R = 2*i + 2, mid = (l + r) / 2;
        return query(L, l, mid, ql, qr) + query(R, mid + 1, r, ql, qr);
    }
    Node query(int l, int r) { return query(0, 0, n - 1, l, r); }
};    

pll mine[MAXN];
int max_r[MAXN], max_l[MAXN];

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            lint x, r;
            scanf("%lld%lld", &x, &r);
            mine[i] = pll(x, r);
        }
        sort(mine, mine + n);
        SegmentTree tree_l(vector<int>(n, INF));
        for (int i = 0; i < n; i++) {
            int l = 0, r = i;
            while (l < r) {
                int mid = (l + r) / 2;
                if (mine[mid].first >= mine[i].first - mine[i].second)
                    r = mid;
                else
                    l = mid + 1;
            }
            max_l[i] = min(tree_l.query(l, i).val, i);
            tree_l.update(i, max_l[i]);
            // printf("max_l[%d] = %d\n", i, max_l[i]);
        }
        SegmentTree tree_r(vector<int>(n, INF));
        for (int i = n - 1; i >= 0; i--) {
            int l = i, r = n - 1;
            while (l < r) {
                int mid = (l + r + 1) / 2;
                if (mine[mid].first <= mine[i].first + mine[i].second)
                    l = mid;
                else
                    r = mid - 1;
            }
            max_r[i] = max(-tree_r.query(i, r).val, i);
            tree_r.update(i, -max_r[i]);
            // printf("max_r[%d] = %d\n", i, max_r[i]);
        }

        for (int i = 0; i < n; i++) {
            int l = i, r = i;
            while (1) {
                int nxt_l = min(tree_l.query(l, r).val, l);
                int nxt_r = max(-tree_r.query(l, r).val, r);
                if (l == nxt_l && r == nxt_r) break;
                l = nxt_l, r = nxt_r;
            }
            printf("%d%c", r - l + 1, i + 1 == n ? '\n' : ' ');
        }
    }        
    return 0;
}
