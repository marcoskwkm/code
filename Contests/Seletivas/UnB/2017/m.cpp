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

int tree[4 * MAXN];
int v[MAXN];

int build(int i, int l, int r) {
    if (l == r) return tree[i] = v[l];
    int L = 2*i + 1, R = 2*i + 2, mid = (l + r) / 2;
    return tree[i] = __gcd(build(L, l, mid), build(R, mid + 1, r));
}

int query(int i, int l, int r, int ql, int qr) {
    if (r < ql || qr < l) return 0;
    if (ql <= l && r <= qr) return tree[i];
    int L = 2*i + 1, R = 2*i + 2, mid = (l + r) / 2;
    return __gcd(query(L, l, mid, ql, qr), query(R, mid + 1, r, ql, qr));
}

int main() {
    int t;x
    for (cin >> t; t--;) {
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++)
            scanf("%d", &v[i]);
        build(0, 1, n);
        for (int i = 0; i < m; i++) {
            int l, r;
            scanf("%d%d", &l, &r);
            printf("%d%c", query(0, 1, n, l, r), i + 1 == m ? '\n' : ' ');
        }
    }
    return 0;
}
