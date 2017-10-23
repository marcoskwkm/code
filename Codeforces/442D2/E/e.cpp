#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)2e5 + 10;

int tree[4 * MAXN];
int lazy[4 * MAXN];
int t[MAXN];
int il[MAXN], ir[MAXN];

void refresh(int i, int l, int r) {
    if (lazy[i] & 1) {
        tree[i] = (r - l + 1) - tree[i];
        if (l < r) {
            int L = 2*i + 1, R = 2*i + 2;
            lazy[L] ^= 1; lazy[R] ^= 1;
        }
    }
    lazy[i] = 0;
}

void update(int i, int l, int r, int ql, int qr) {
    // debug("update %d %d %d %d\n", l, r, ql, qr);
    refresh(i, l, r);
    if (ql > r || l > qr) return;
    if (ql <= l && r <= qr) {
        lazy[i] ^= 1;
        refresh(i, l, r);
        return;
    }
    int L = 2*i + 1, R = 2*i + 2, mid = (l + r) / 2;
    update(L, l, mid, ql, qr); update(R, mid + 1, r, ql, qr);
    tree[i] = tree[L] + tree[R];
}

int query(int i, int l, int r, int ql, int qr) {
    // debug("query %d %d %d %d\n", l, r, ql, qr);
    refresh(i, l, r);
    if (ql > r || l > qr) return 0;
    if (ql <= l && r <= qr) return tree[i];
    int L = 2*i + 1, R = 2*i + 2, mid = (l + r) / 2;
    return query(L, l, mid, ql, qr) + query(R, mid + 1, r, ql, qr);
}    

vector<int> adj[MAXN];

void dfs(int v) {
    // debug("dfs %d\n", v);
    static int cnt = 0;
    il[v] = cnt;
    for (int nxt: adj[v]) dfs(nxt);
    ir[v] = cnt++;
}

int main() {
    int n;
    cin >> n;
    for (int i = 2; i <= n; i++) {
        int p;
        scanf("%d", &p);
        adj[p].push_back(i);
    }
    for (int i = 1; i <= n; i++)
        scanf("%d", &t[i]);
    dfs(1);
    for (int i = 1; i <= n; i++) {
        // debug("%d: %d\n", i, ir[i]);
        if (t[i]) update(0, 0, n - 1, ir[i], ir[i]);
    }
    int q;
    for (cin >> q; q--;) {
        char op[10];
        int v;
        scanf(" %s%d", op, &v);
        if (op[0] == 'g') printf("%d\n", query(0, 0, n - 1, il[v], ir[v]));
        else update(0, 0, n - 1, il[v], ir[v]);
    }
    return 0;
}
