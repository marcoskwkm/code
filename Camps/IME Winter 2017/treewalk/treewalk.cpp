#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e6 + 10;

vector<int> adj[MAXN];
int q[MAXN];
lint ans[MAXN];
int maxd[MAXN];
lint sum[MAXN];
int n;

void dfs(int v, int prv) {
    q[v] = 1;
    maxd[v] = 0;
    for (int nxt: adj[v]) {
        if (nxt == prv) continue;
        dfs(nxt, v);
        q[v] += q[nxt];
        maxd[v] = max(maxd[v], 1 + maxd[nxt]);
        sum[v] += sum[nxt] + 2 * q[nxt];
    }
}

void go(int v, int prv, int up, lint sumup) {
    // printf("%d %d %d %lld\n", v, prv, up, sumup);
    int hi = up, hi2 = 0;
    int maxq = n - q[v];
    int maxat = 0;
    for (int nxt: adj[v]) {
        if (nxt == prv) continue;
        if (maxd[nxt] + 1 >= hi) {
            hi2 = hi;
            hi = maxd[nxt] + 1;
        }
        else if (maxd[nxt] + 1 > hi2)
            hi2 = maxd[nxt] + 1;
        if (q[nxt] > maxq) {
            maxq = q[nxt];
            maxat = nxt;
        }
    }
    // printf("hi = %d, hi2 = %d\n", hi, hi2);
    if (maxq > n / 2) ans[v] = -1;
    else {
        if (maxq == n / 2) {
            // printf("oi! maxat = %d, maxd = %d\n", maxat, maxd[maxat]);
            int rem = maxd[maxat] + 1;
            if (maxat == 0) rem = up;
            ans[v] = sumup + sum[v] - rem;
        }
        else
            ans[v] = sumup + sum[v] - hi;
    }
    for (int nxt: adj[v]) {
        if (nxt == prv) continue;
        lint nxtsumup = sumup + sum[v] - sum[nxt] - 2 * q[nxt];
        nxtsumup += 2 * (n - q[nxt]);
        go(nxt, v, (maxd[nxt] + 1 == hi ? hi2 : hi) + 1, nxtsumup);
    }
}

int main() {
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, -1);
    go(1, -1, 0, 0);
    for (int i = 1; i <= n; i++)
        printf("%lld\n", ans[i]);    
    return 0;
}
