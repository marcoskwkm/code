#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)5e5 + 10;
const int MOD = (int)1e9 + 7;

int tree[4*MAXN];

int update(int i, int l, int r, int x, int val) {
    if (r < x || l > x) return tree[i];
    if (l == r) return tree[i] = val;
    int L = 2*i + 1, R = 2*i + 2, mid = (l + r) / 2;
    return tree[i] = max(update(L, l, mid, x, val), update(R, mid + 1, r, x, val));
}

int query(int i, int l, int r, int ql, int qr) {
    if (r < ql || l > qr) return -1;
    if (ql <= l && r <= qr) return tree[i];
    int L = 2*i + 1, R = 2*i + 2, mid = (l + r) / 2;
    return max(query(L, l, mid, ql, qr), query(R, mid + 1, r, ql, qr));
}

void print(int i, int l, int r) {
    debug("[%d, %d]: %d\n", l, r, tree[i]);
    if (l < r) {
        int L = 2*i + 1, R = 2*i + 2, mid = (l + r)/2;
        print(L, l, mid);
        print(R, mid + 1, r);
    }
}

int v[MAXN];
lint dp[MAXN];
lint acc[MAXN];

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++)
        scanf("%d", &v[i]);
    fill(tree, tree + 4*MAXN, n);

    k = min(k, n);
    dp[n] = 1;
    acc[n] = 1;    
    for (int i = n - 1; i >= 0; i--) {
        if (v[i] <= k) {
            update(0, 0, n, v[i], i);
        }           
        int last_pos = query(0, 0, n, 0, k);
        dp[i] = ((acc[i + 1] - acc[last_pos + 1]) % MOD + MOD)%MOD;
        acc[i] = (dp[i] + acc[i + 1]) % MOD;
    }

    printf("%lld\n", dp[0]);    
    return 0;
}
