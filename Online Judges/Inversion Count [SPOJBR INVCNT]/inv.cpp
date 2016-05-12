#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)2e5 + 10;

int v[MAXN], aux[MAXN];

lint merge(int l, int r) {
    if (l == r) return 0;
    int mid = (l + r) / 2;
    lint ret = merge(l, mid) + merge(mid + 1, r);
    int ll = l, rr = mid + 1, cur = l;
    while (ll <= mid) {
        while (rr <= r && v[rr] < v[ll]) {
            aux[cur++] = v[rr++];
            ret += mid - ll + 1;
        }
        aux[cur++] = v[ll++];
    }
    while (rr <= r) aux[cur++] = v[rr++];
    for (int i = l; i <= r; i++) v[i] = aux[i];
    return ret;
}

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) scanf("%d", &v[i]);
        printf("%lld\n", merge(0, n - 1));
    }
    return 0;
}
