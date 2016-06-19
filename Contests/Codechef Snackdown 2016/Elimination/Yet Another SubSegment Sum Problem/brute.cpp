#include <bits/stdc++.h>
using namespace std;

typedef long long lint;

const int MAXN = (int)1e5 + 10;

lint A[MAXN], B[MAXN];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &A[i]);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &B[i]);
    int q;
    for (scanf("%d", &q); q--;) {
        lint l, r, c, d;
        scanf("%lld%lld%lld%lld", &l, &r, &c, &d);
        lint ans = 0;
        for (int i = l; i <= r; i++) {
            ans += max(0ll, A[i]*c - B[i]*d);
        }
        printf("%lld\n", ans);
        fflush(stdout);
    }
    return 0;
}
