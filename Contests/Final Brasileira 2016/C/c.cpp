#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 1010;
const int MOD = (int)1e9 + 7;

lint x[MAXN], y[MAXN];
lint ans[MAXN];

lint ch[MAXN][MAXN];
lint choose(int n, int k) {
    k = min(k, n - k);
    if (k < 0) return 0;
    if (k == 0) return 1;
    if (ch[n][k] != -1) return ch[n][k];
    return ch[n][k] = (choose(n - 1, k - 1) + choose(n - 1, k)) % MOD;
}

int main() {
    int n;
    scanf("%d", &n);
    set<pii> cj;
    map<pii, int> q;
    for (int i = 0; i < n; i++) {
        scanf("%lld%lld", &x[i], &y[i]);
        x[i] *= 2;
        y[i] *= 2;
        cj.insert(pii(x[i], y[i]));
        q[pii(x[i], y[i])] = 0;
    }
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            q[pii((x[i] + x[j]) / 2, (y[i] + y[j]) / 2)]++;

    memset(ch, -1, sizeof(ch));
    for (const auto &p: q) {
        for (int take = 1; take <= p.second; take++)
            ans[2*take] += choose(p.second, take);
        if (cj.find(p.first) != cj.end())
            for (int take = 0; take <= p.second; take++)
                ans[2*take + 1] += choose(p.second, take);
    }

    for (int i = 1; i <= n; i++)
        printf("%lld%c", ans[i] % MOD, i == n ? '\n' : ' ');    
    return 0;
}
