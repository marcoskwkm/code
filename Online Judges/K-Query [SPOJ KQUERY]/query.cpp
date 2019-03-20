#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)3e5 + 10;
const int MAXND = (int)1e6 + 10;
const int MAXV = (int)1e9;

struct Node {
    int val;
    Node *l, *r;
} nodes[MAXND];

int data_cnt = 0;
inline Node *newnode() {
    nodes[data_cnt].val = 0;
    nodes[data_cnt].l = nodes[data_cnt].r = 0;
    return &nodes[data_cnt++];
}
inline Node *newnode(Node* node) {
    nodes[data_cnt].val = node->val;
    return &nodes[data_cnt++];
}

Node* update(Node *tree, int l, int r, int x, int val) {
    if (x < l || x > r) return tree;
    Node *upd = newnode(tree);
    upd->val += val;
    if (l == r) return upd;
    int m = (l + r) / 2;
    if (tree->l == NULL) tree->l = newnode();
    if (tree->r == NULL) tree->r = newnode();
    upd->l = update(tree->l, l, m, x, val);
    upd->r = update(tree->r, m + 1, r, x, val);
    return upd;
}

int query(Node *tree, int l, int r, int ql, int qr) {
    if (tree == NULL) return 0;
    if (qr < l || r < ql) return 0;
    if (ql <= l && r <= qr) return tree->val;    
    int m = (l + r) / 2;
    return query(tree->l, l, m, ql, qr) + query(tree->r, m + 1, r, ql, qr);
}

int main() {
    int n;
    cin >> n;
    vector<pii> v;
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        v.push_back(pii(x, i));
    }

    sort(v.begin(), v.end(), greater<pii>());

    Node *tree = newnode();
    vector<Node*> roots = {tree};
    for (int i = 0; i < n; i++) {
        roots.push_back(update(roots.back(), 0, n - 1, v[i].second, 1));
    }

    int q;
    for (cin >> q; q--;) {
        int i, j, k;
        scanf("%d%d%d", &i, &j, &k);
        int l = 0, r = n;
        int pos = upper_bound(v.begin(), v.end(), pii(k, 0), greater<pii>()) - v.begin();
        // while (l < r) {
        //     int m = (l + r + 1) / 2;
        //     if (v[m - 1].first > k) l = m;
        //     else r = m - 1;
        // }
        printf("%d\n", query(roots[pos - 1], 0, n - 1, i - 1, j - 1));
        // printf("%d\n", query(roots[0], 0, n - 1, i - 1, j - 1));
    }    
    return 0;
}
