#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)2e5 + 10;

/* A directed graph */
struct Graph {
    int V;
    vector<vector<int>> adj;
    
    Graph(int _V) : V(_V) {
        adj.resize(V);
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
    }
};

int color[MAXN];
int rev[MAXN];
vector<int> comp[MAXN][2];
vector<int> f[MAXN];
int dp[MAXN], prv[MAXN];

int dfs(int v, int c, int cmp, const Graph &g) {
    color[v] = c;
    comp[cmp][c].push_back(v);
    int diff = (c == 1 ? 1 : -1);
    for (int nxt: g.adj[v])
        if (color[nxt] == -1)
            diff += dfs(nxt, c ^ 1, cmp, g);
    return diff;
}            

int main() {
    int n, m;
    cin >> n >> m;
    Graph g(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        g.add_edge(u, v);
        g.add_edge(v, u);
    }
    memset(color, -1, sizeof(color));
    int n_comps = 0;
    int total_diff = 0;
    for (int v = 1; v <= n; v++) {
        if (color[v] == -1) {
            int diff = dfs(v, 0, n_comps, g);
            total_diff += abs(diff);
            if (diff < 0) rev[n_comps] = 1;
            f[abs(diff)].push_back(n_comps);
            n_comps++;
        }
    }

    memset(dp, INF, sizeof(dp));
    dp[0] = 0;
    prv[0] = -1;
    for (int d = 1; d < n; d++) {
        if (f[d].empty()) continue;
        for (int i = 0; i + d <= n; i++)
            dp[i + d] = min(dp[i + d], dp[i] + 1);
        for (int i = 1; i <= n; i++) {
            if (dp[i] > (int)f[d].size())
                dp[i] = INF;
            else if (dp[i] > 0) {
                dp[i] = 0;
                prv[i] = d;
            }
        }
    }

    int ans = INF, at;
    for (int i = 0; 2 * i <= total_diff; i++) {
        if (dp[i] == 0 && ans > total_diff - 2 * i) {
            ans = total_diff - 2 * i;
            at = i;
        }
    }
    while (at > 0) {
        rev[f[prv[at]].back()] ^= 1;
        f[prv[at]].pop_back();
        at -= prv[at];
    }

    int wv, iw = -1, bv, ib = -1;
    for (int i = 0; i < n_comps; i++) {
        if (!comp[i][rev[i]].empty()) {
            wv = comp[i][rev[i]][0];
            iw = i;
        }
        if (!comp[i][rev[i]^1].empty()) {
            bv = comp[i][rev[i]^1][0];
            ib = i;
        }
    }

    vector<pii> sol;
    if (iw != ib) sol.push_back(pii(wv, bv));
    for (int i = 0; i < n_comps; i++) {
        if (i == iw || i == ib) continue;
        if (!comp[i][rev[i]].empty())
            sol.push_back(pii(bv, comp[i][rev[i]][0]));
        else
            sol.push_back(pii(wv, comp[i][rev[i]^1][0]));
    }    
    printf("%d %d\n", ans, (int)sol.size());
    for (pii p: sol) printf("%d %d\n", p.first, p.second);
    return 0;
}
