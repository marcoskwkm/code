#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;
const int LOG = 20;

int v[MAXN];
int q[MAXN];
int last[MAXN];

lint tree[4 * MAXN];
lint lazy[4 * MAXN];

void refresh(int i, int l, int r) {
    tree[i] += lazy[i];
    if (l != r) {
        int L = 2 * i + 1, R = 2 * i + 2;
        lazy[L] += lazy[i];
        lazy[R] += lazy[i];
    }
    lazy[i] = 0;
}    

void update(int i, int l, int r, int ql, int qr, int x) {
    refresh(i, l, r);
    if (r < ql || l > qr) return;
    if (ql <= l && r <= qr) {
        lazy[i] += x;
        refresh(i, l, r);
        return;
    }
    int L = 2 * i + 1, R = 2 * i + 2, mid = (l + r) / 2;
    update(L, l, mid, ql, qr, x);
    update(R, mid + 1, r, ql, qr, x);
    tree[i] = min(tree[L], tree[R]);
}

lint query(int i, int l, int r, int ql, int qr) {
    refresh(i, l, r);
    if (r < ql || l > qr) return INF;
    if (ql <= l && r <= qr) return tree[i];
    int L = 2 * i + 1, R = 2 * i + 2, mid = (l + r) / 2;
    return min(query(L, l, mid, ql, qr), query(R, mid + 1, r, ql, qr));
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &v[i]);
    for (int i = 1; i <= m; i++)
        scanf("%d", &q[i]);

    memset(last, -1, sizeof(last));
    int ans = -1;
    set<int> active;
    for (int i = n; i > 0; i--) {
        if (v[i] == 0) {
            update(0, 1, n, i, i, INF);
            continue;
        }
        int take = 1 + q[v[i]];
        if (last[v[i]] != -1) {
            update(0, 1, n, last[v[i]], last[v[i]], INF);
            if (last[v[i]] < n) update(0, 1, n, last[v[i]] + 1, n, take);
            active.erase(last[v[i]]);
        }
        last[v[i]] = i;
        active.insert(i);
        update(0, 1, n, i, i, i - take);
        if (i < n - 1) update(0, 1, n, i + 1, n, -take);
        if (query(0, 1, n, i, n) >= 0) {
            if ((int)active.size() == m)
                ans = *active.rbegin();
        }
        else break;
    }
    printf("%d\n", ans);        
    return 0;
}
