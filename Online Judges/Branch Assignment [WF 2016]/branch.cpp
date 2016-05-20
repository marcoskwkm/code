#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef pair<lint, pii> plp;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 5010;

lint dist[2][MAXN];
vector<pii> adj[2][MAXN];

void dijkstra(int s, int k) {
    dist[k][s] = 0;
    set<pll> pq;
    pq.insert(pll(0, s));
    while (!pq.empty()) {
        pll cur = *pq.begin();
        pq.erase(pq.begin());
        int v = cur.second;
        for (pii edge: adj[k][v]) {
            int nxt = edge.first, cst = edge.second;
            if (dist[k][nxt] > dist[k][v] + cst) {
                pq.erase(pll(dist[k][nxt], nxt));
                dist[k][nxt] = dist[k][v] + cst;
                pq.insert(pll(dist[k][nxt], nxt));
            }
        }
    }
}

lint cost[MAXN][MAXN];
bool foi[MAXN];
lint dp[MAXN][MAXN];
lint acc[MAXN];
int idx[MAXN];

lint get(int i, int j, int k) {
    return (i - j - 1) * (acc[i] - acc[j]) + dp[k - 1][j];
}

void solve(int k, int l, int r, int opt_l, int opt_r) {
    if (l > r) return;
    int mid = (l + r) / 2;
    lint best = LINF;
    int opt = -1;
    for (int i = opt_l; i <= min(mid - 1, opt_r); i++) {
        lint got = get(mid, i, k);
        if (got < best) {
            best = got;
            opt = i;
        }
    }
    dp[k][mid] = best;
    solve(k, l, mid - 1, opt_l, opt);
    solve(k, mid + 1, r, opt, opt_r);
}        

int main() {
    int n, b, s, r;
    scanf("%d%d%d%d", &n, &b, &s, &r);
    for (int i = 0; i < r; i++) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        adj[0][u].push_back(pii(v, c));
        adj[1][v].push_back(pii(u, c));
    }    
    memset(dist, INF, sizeof(dist));
    dijkstra(b + 1, 0); dijkstra(b + 1, 1);

    for (int i = 1; i <= b; i++)
        idx[i] = i;
    sort(idx + 1, idx + b + 1, [](int a, int b) {
        return dist[0][a] + dist[1][a] < dist[0][b] + dist[1][b];
    });
    for (int i = 1; i <= b; i++) {
        acc[i] = acc[i - 1] + dist[0][idx[i]] + dist[1][idx[i]];
    }
    
    memset(dp, INF, sizeof(dp));
    for (int i = 1; i <= b; i++)
        dp[1][i] = (i - 1) * acc[i];

    for (int k = 2; k <= s; k++) {
        solve(k, 1, b, 1, b);
        // int opt = 0;
        // for (int i = 1; i <= b; i++) {
        //     while (opt + 1 < i && get(i, opt, k) > get(i, opt + 1, k)) opt++;
        //     dp[k][i] = get(i, opt, k);
        //     debug("dp[%d][%d] = %lld\n", k, i, dp[k][i]);
        // }
    }

    printf("%lld\n", dp[s][b]);
    return 0;
}
