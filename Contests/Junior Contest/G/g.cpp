#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;

lint tree[4 * MAXN];
int v[MAXN];

void build(int i, int l, int r) {
    if (l == r) {
        tree[i] = v[l];
        return;
    }
    int L = 2*i + 1, R = 2*i + 2, mid = (l + r)/2;
    build(L, l, mid); build(R, mid + 1, r);
    tree[i] = tree[L] + tree[R];
}

void update(int i, int l, int r, int x, int val) {
    if (l > x || r < x) return;
    if (l == r) {
        tree[i] = val;
        return;
    }
    int L = 2*i + 1, R = 2*i + 2, mid = (l + r)/2;
    update(L, l, mid, x, val); update(R, mid + 1, r, x, val);
    tree[i] = tree[L] + tree[R];
}

lint query(int i, int l, int r, int ql, int qr) {
    if (l > qr || r < ql) return 0;
    if (ql <= l && r <= qr) return tree[i];
    int L = 2*i + 1, R = 2*i + 2, mid = (l + r)/2;
    return query(L, l, mid, ql, qr) + query(R, mid + 1, r, ql, qr);
}

struct Query {
    int x, y, idx, t;
    Query(int a, int b, int c, int d) {
        x = a; y = b; idx = c; t = d;
    }
};

lint ans[MAXN];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", &v[i]);
    build(0, 0, n - 1);
    vector<Query> queries;
    vector<Query> updates;
    int q;
    scanf("%d", &q);
    int nq = 0;
    for (int i = 0; i < q; i++) {
        char op;
        scanf(" %c", &op);
        if (op == 'Q') {
            int x, y, k;
            scanf("%d%d%d", &x, &y, &k);
            queries.push_back(Query(x - 1, y - 1, nq++, k));
        }
        else {
            int x, y;
            scanf("%d%d", &x, &y);
            updates.push_back(Query(x - 1, y, 0, 0));
        }
    }
    sort(queries.begin(), queries.end(), [](Query a, Query b) {
        return a.t < b.t;
    });
    int at = 0;
    for (int t = 0; t <= (int)updates.size(); t++) {
        while (at < (int)queries.size() && queries[at].t == t) {
            ans[queries[at].idx] = query(0, 0, n - 1, queries[at].x, queries[at].y);
            at++;
        }
        if (t < (int)updates.size()) update(0, 0, n - 1, updates[t].x, updates[t].y);
    }
    for (int i = 0; i < nq; i++)
        cout << ans[i] << endl;
    return 0;
}
