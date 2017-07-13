#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXQ = (int)1e6 + 10;

lint tree[4 * MAXQ];
lint lazy[4 * MAXQ];

void refresh(int i, int l, int r) {
    tree[i] += lazy[i];
    if (l < r) {
        int L = 2*i + 1, R = 2*i + 2;
        lazy[L] += lazy[i];
        lazy[R] += lazy[i];
    }
    lazy[i] = 0;
}

lint update(int i, int l, int r, int ql, int qr, int val) {
    refresh(i, l, r);
    if (r < ql || l > qr) return tree[i];
    if (ql <= l && r <= qr) {
        lazy[i] += val;
        refresh(i, l, r);
        return tree[i];
    }
    int L = 2*i + 1, R = 2*i + 2, mid = (l + r) / 2;
    return tree[i] = max(update(L, l, mid, ql, qr, val),
                         update(R, mid + 1, r, ql, qr, val));
}

lint query(int i, int l, int r, int ql, int qr) {
    refresh(i, l, r);
    if (r < ql || l > qr) return 0;
    if (ql <= l && r <= qr) return tree[i];
    int L = 2*i + 1, R = 2*i + 2, mid = (l + r) / 2;
    return max(query(L, l, mid, ql, qr),
               query(R, mid + 1, r, ql, qr));
}    

int seq[MAXQ];
int val[MAXQ];
int last[MAXQ], prv[MAXQ];

int main() {
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++)
        scanf("%d", &seq[i]);
    for (int i = 1; i <= q; i++)
        scanf("%d", &val[i]);

    memset(prv, -1, sizeof(prv));
    lint ans = 0;
    for (int i = 1; i <= n; i++) {
        int cur = seq[i - 1];
        // printf("i = %d (%d, %d)\n", i, cur, val[cur]);
        if (last[cur] != 0) {
            update(0, 0, n, prv[cur] + 1, last[cur], -val[cur]);
            // printf("update [%d, %d] %d\n", prv[cur] + 1, last[cur], -val[cur]);
        }
        update(0, 0, n, last[cur] + 1, i, val[cur]);
        // printf("update [%d, %d] %d\n", last[cur] + 1, i, val[cur]);
        prv[cur] = last[cur];
        last[cur] = i;
        ans = max(ans, query(0, 0, n, 1, i));
    }
    cout << ans << endl;    
    return 0;
}
