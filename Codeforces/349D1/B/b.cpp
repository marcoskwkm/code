#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 3010;

vector<int> adj[MAXN];
int dist[MAXN][MAXN];
vector<pii> to[MAXN], from[MAXN];

void bfs(int s) {
    dist[s][s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int nxt: adj[v]) {
            if (dist[s][nxt] == INF) {
                dist[s][nxt] = dist[s][v] + 1;
                q.push(nxt);
            }
        }
    }
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    memset(dist, INF, sizeof(dist));
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
    }
    for (int v = 1; v <= n; v++) {
        bfs(v);
        for (int u = 1; u <= n; u++) {
            if (u == v) continue;
            if (dist[v][u] == INF) continue;
            to[u].push_back(pii(dist[v][u], v));
            from[v].push_back(pii(dist[v][u], u));
        }
    }
    for (int v = 1; v <= n; v++) {
        sort(to[v].begin(), to[v].end(), greater<pii>());
        sort(from[v].begin(), from[v].end(), greater<pii>());
    }

    int ans = 0;
    vector<int> sol;
    for (int b = 1; b <= n; b++) {
        for (int c = 1; c <= n; c++) {
            if (b == c) continue;
            if (dist[b][c] == INF) continue;
            int lb = min<int>(5, to[b].size());
            int lc = min<int>(5, from[c].size());
            for (int i = 0; i < lb; i++) {
                int a = to[b][i].second;
                if (a == c) continue;
                for (int j = 0; j < lc; j++) {
                    int d = from[c][j].second;
                    if (d == a || d == b || d == c) continue;
                    int got = dist[a][b] + dist[b][c] + dist[c][d];
                    if (got > ans) {
                        ans = got;
                        sol = {a, b, c, d};
                    }
                }
            }
        }
    }
    printf("%d %d %d %d\n", sol[0], sol[1], sol[2], sol[3]);
    return 0;
}
