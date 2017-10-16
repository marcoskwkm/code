#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 110;

vector<int> adj[MAXN];
int dist[MAXN][MAXN];
int ans[MAXN][MAXN][2];

void bfs(int s) {
    memset(dist[s], INF, sizeof(dist[s]));
    dist[s][s] = 0;
    queue<int> q({s});
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
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int s = 1; s <= n; s++)
        bfs(s);

    memset(ans, INF, sizeof(ans));
    queue<pii> q;
    for (int i = 1; i <= n; i++) {
        q.push(pii(i, i));
        ans[i][i][1] = 0;
        ans[i][i][0] = 0;
    }
    do {
        while (!q.empty()) {
            int i, j;
            tie(i, j) = q.front();
            q.pop();
            for (int nxt: adj[i]) {
                if (ans[nxt][j][0] == INF) {
                    ans[nxt][j][0] = 1 + ans[i][j][1];
                }
            }
            if (ans[i][j][0] == INF)
                ans[i][j][0] = 1 + ans[i][j][1];
        }
        for (int i = 1; i <= n; i++) {
            for (int jj = 1; jj <= n; jj++) {
                if (ans[i][jj][1] != INF) continue;
                int hi = ans[i][jj][0];
                for (int nxt: adj[jj])
                    hi = max(hi, ans[i][nxt][0]);
                if (hi != INF) {
                    ans[i][jj][1] = 1 + hi;
                    q.push(pii(i, jj));
                }
            }
        }
    } while(!q.empty());

    // for (int i = 1; i <= n; i++)
    //     for (int j = 1; j <= n; j++)
    //         for (int k = 0; k < 2; k++)
    //             debug("ans(%d, %d, %d) = %d\n", i, j, k, ans[i][j][k]);

    int start = -1, best = INF;
    for (int s = 1; s <= n; s++) {
        int hi = 0;
        for (int t = 1; t <= n; t++)
            hi = max(hi, ans[s][t][0]);
        if (hi < best) {
            best = hi;
            start = s;
        }
    }

    int s = start, t;
    printf("%d\n", s);
    fflush(stdout);
    scanf("%d", &t);
    while (s != t) {
        int nxt = -1, best = INF;
        for (int ss: adj[s]) {
            if (ans[ss][t][1] < best) {
                best = ans[ss][t][1];
                nxt = ss;
            }
        }
        s = nxt;
        printf("%d\n", s);
        fflush(stdout);
        if (s == t) break;
        scanf("%d", &t);
    }    
    return 0;
}
