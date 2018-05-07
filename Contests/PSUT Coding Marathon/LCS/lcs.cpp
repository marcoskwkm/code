#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 30;

int dp[MAXN][MAXN];
vector<int> adj[2][MAXN];
bool seen[2][MAXN];
bool can_equal[MAXN][MAXN], can_diff[MAXN][MAXN];
char ans[2][MAXN];

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

void dfs(int i, int j, vector<pii> &v) {
    seen[i][j] = 1;
    v.push_back(pii(i, j));
    for (int nxt: adj[i][j])
        if (!seen[i ^ 1][nxt])
            dfs(i ^ 1, nxt, v);
}

int color[2 * MAXN];
bool go(const Graph &g, int i) {
    if (i == g.V) return 1;
    for (int c = 0; c < 26; c++) {
        bool ok = 1;
        for (int nxt: g.adj[i]) {
            if (nxt > i) continue;
            if (color[nxt] == c) {
                ok = 0;
                break;
            }
        }
        if (ok) {
            color[i] = c;
            if (go(g, i + 1)) return 1;
        }
    }
    return 0;
}

void solve(int R, int C) {
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < MAXN; j++)
            adj[i][j].clear();
    
    for (int r = 0; r <= R; r++) {
        for (int c = 0; c <= C; c++) {
            scanf("%d", &dp[r][c]);
            if (r == 0 || c == 0) continue;
            can_equal[r][c] = (dp[r][c] == dp[r - 1][c - 1] + 1);
            can_diff[r][c] = (dp[r][c] == max(dp[r - 1][c], dp[r][c - 1]));
            if (can_equal[r][c] && !can_diff[r][c]) {
                adj[0][r].push_back(c);
                adj[1][c].push_back(r);
            }
        }
    }

    vector<vector<pii>> comps;
    for (int r = 1; r <= R; r++) {
        if (!seen[0][r]) {
            vector<pii> comp;
            dfs(0, r, comp);
            comps.push_back(comp);
        }
    }
    for (int c = 1; c <= C; c++) {
        if (!seen[1][c]) {
            vector<pii> comp;
            dfs(1, c, comp);
            comps.push_back(comp);
        }
    }

    Graph g(comps.size());
    for (size_t i = 0; i < comps.size(); i++) {
        for (size_t j = i + 1; j < comps.size(); j++) {
            bool has = 0;
            for (pii pi: comps[i]) {
                for (pii pj: comps[j]) {
                    if (pi.first == pj.first) continue;
                    int x = pi.second, y = pj.second;
                    if (pi.first == 1) swap(x, y);
                    if (!can_equal[x][y]) {
                        has = 1;
                        break;
                    }
                }
                if (has) break;
            }
            if (has) {
                g.add_edge(i, j);
                g.add_edge(j, i);
            }
        }
    }

    memset(color, -1, sizeof(color));
    assert(go(g, 0));

    for (size_t i = 0; i < comps.size(); i++)
        for (const auto &p: comps[i])
            ans[p.first][p.second - 1] = 'a' + color[i];
    
    ans[0][R] = ans[1][C] = 0;
    printf("%s\n%s\n", ans[0], ans[1]);    
}                    

int main() {
    int R, C;
    cin >> R >> C;
    solve(R, C);
    return 0;
}
