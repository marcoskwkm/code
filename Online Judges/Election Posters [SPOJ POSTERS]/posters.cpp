#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

struct SegmentTree {
    typedef int D_TYPE; // data type
    
    struct Node {
        D_TYPE val, lazy;
        bool flag;
        Node(int v = 0) { val = v; flag = 0; }
    };

    vector<Node> tree;
    int N;

    SegmentTree(int n) { N = n; tree.resize(4*n + 1); }

    inline D_TYPE merge(D_TYPE dl, D_TYPE dr) {
        // customize
        return max(dl, dr);
    }

    void build(int i, int l, int r, int *v) {
        if (l == r) { tree[i].val = v[l]; tree[i].flag = 0; }
        else {
            int L = 2*i + 1, R = 2*i + 2, mid = (l + r)/2;
            build(L, l, mid, v); build(R, mid + 1, r, v);
            tree[i].val = merge(tree[L].val, tree[R].val);
        }
    }
    
    void init(int *v) { build(0, 0, N - 1, v); }

    void refresh(int i) {
        // customize
        if (!tree[i].flag) return;
        tree[i].flag = 0;
        tree[i].val = tree[i].lazy;
        int L = 2*i + 1, R = 2*i + 2;
        if (L >= 4*N) return;
        tree[L].flag = tree[R].flag = 1;
        tree[L].lazy = tree[R].lazy = tree[i].lazy;
    }

    void _update(int i, int l, int r, int ql, int qr, int val) {
        refresh(i);
        if (r < ql || l > qr) return;
        if (ql <= l && r <= qr) {
            // customize
            tree[i].flag = 1;
            tree[i].lazy = val;
            refresh(i);
            return;
        }
        int L = 2*i + 1, R = 2*i + 2, mid = (l + r)/2;
        _update(L, l, mid, ql, qr, val);
        _update(R, mid + 1, r, ql, qr, val);
        tree[i].val = merge(tree[L].val, tree[R].val);
    }

    void update(int l, int r, int val) { _update(0, 0, N - 1, l, r, val); }

    D_TYPE _query(int i, int l, int r, int ql, int qr) {
        refresh(i);
        if (r < ql || l > qr) return -INF; // customize
        if (ql <= l && r <= qr) return tree[i].val;
        // customize
        int L = 2*i + 1, R = 2*i + 2, mid = (l + r)/2;
        D_TYPE dl = _query(L, l, mid, ql, qr);
        D_TYPE dr = _query(R, mid + 1, r, ql, qr);
        return merge(dl, dr);
    }

    D_TYPE query(int l, int r) { return _query(0, 0, N - 1, l, r); }
};

const int MAXN = (int)4e4 + 10;
const int MAXV = (int)1e7 + 10;

pii posters[MAXN];
int mp[MAXV];

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        SegmentTree tree(MAXN);
        int n;
        scanf("%d", &n);
        set<int> cj;
        for (int i = 1; i <= n; i++) {
            scanf("%d%d", &posters[i].first, &posters[i].second);
            cj.insert(posters[i].first); cj.insert(posters[i].second);
        }
        int cur = 0;
        for (int x: cj)
            mp[x] = cur++;

        for (int i = 1; i <= n; i++)
            tree.update(mp[posters[i].first], mp[posters[i].second], i);
        
        set<int> ans;
        for (int p = 0; p < cur; p++)
            ans.insert(tree.query(p, p));
        
        printf("%d\n", (int)ans.size());
    }            
    return 0;
}
