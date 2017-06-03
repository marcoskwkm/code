#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)4e5 + 10;
const int MAXD = (int)2e7 + 10;

struct Node {
    lint val;
    lint lazy;
    Node *l, *r;
    void refresh(int l, int r);
};
    
Node data[MAXD];
int data_cnt;

Node* newnode(lint v) {
    data[data_cnt].val = v;
    data[data_cnt].lazy = 0;
    data[data_cnt].l = data[data_cnt].r = NULL;
    return &data[data_cnt++];
}

Node* copynode(Node *old) {
    data[data_cnt].val = old->val;
    data[data_cnt].lazy = old->lazy;
    data[data_cnt].l = old->l;
    data[data_cnt].r = old->r;
    return &data[data_cnt++];
}

void Node::refresh(int ll, int rr) {
    val += lazy * (rr - ll + 1);
    if (l != NULL) {
        l = copynode(l);
        r = copynode(r);
        l->lazy += lazy;
        r->lazy += lazy;
    }
    lazy = 0;
}

Node *tree[MAXN];

Node* update(Node *t, int l, int r, int ql, int qr) {
    t->refresh(l, r);
    Node *node = copynode(t);
    if (r < ql || qr < l) return node;
    if (ql <= l && r <= qr) {
        node->lazy++;
        node->refresh(l, r);
        return node;
    }
    int mid = (l + r) / 2;
    node->l = update(node->l, l, mid, ql, qr);
    node->r = update(node->r, mid + 1, r, ql, qr);
    node->val = node->l->val + node->r->val;
    return node;
}

lint query(Node *t, int l, int r, int ql, int qr) {
    t->refresh(l, r);
    if (r < ql || qr < l) return 0;
    if (ql <= l && r <= qr) return t->val;
    int mid = (l + r) / 2;
    return query(t->l, l, mid, ql, qr) + query(t->r, mid + 1, r, ql, qr);
}

Node* build(int l, int r) {
    Node *node = newnode((int)0);
    if (l != r) {
        int mid = (l + r) / 2;
        node->l = build(l, mid);
        node->r = build(mid + 1, r);
    }
    return node;
}

void build_tree(int n, int *r) {
    tree[n] = build(0, n - 1);
    for (int l = n - 1; l >= 0; l--) {
        tree[l] = update(tree[l + 1], 0, n - 1, l, r[l]);
    }
}

int v[MAXN];
int dp[32][MAXN][2];
int nxt_one[32][MAXN];
int vv[MAXN];
int n;

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }
    for (int i = 0; i < n; i++) {
        int cur = v[i];
        int j = i;
        while (j + 1 < n && (cur ^ v[j + 1]) >= cur) {
            cur ^= v[j];
            j++;
        }
        vv[i] = j;
        debug("vv[%d] = %d\n", i, vv[i]);
    }

    build_tree(n, vv);
    int q;
    lint ans = 0;
    for (scanf("%d", &q); q--;) {
        int a, b;
        scanf("%d%d", &a, &b);
        int l = (a + ans) % n + 1;
        int r = (b + ans) % n + 1;
        ans = query(tree[l], 0, n - 1, l - 1, r - 1);
        debug("l = %d, r = %d\n", l, r);
        printf("%lld\n", ans);
    }    
    return 0;
}
