#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;

vector<int> adj[MAXN];
int dist[2][MAXN];

void bfs(int s, int k) {
    dist[k][s] = 0;
    queue<int> fila;
    fila.push(s);
    while (!fila.empty()) {
        int v = fila.front();
        fila.pop();
        for (int nxt: adj[v]) {
            if (dist[k][nxt] != INF) continue;
            dist[k][nxt] = dist[k][v] + 1;
            fila.push(nxt);
        }
    }
}

bool foi[MAXN];

int dfs(int v, int length) {
    foi[v] = 1;
    int ret = length;
    for (int nxt: adj[v]) {
        if (foi[nxt]) continue;
        if (dist[0][nxt] == dist[0][v] - 1 &&
            dist[1][nxt] == dist[1][v] - 1) {
            ret = max(ret, dfs(nxt, length + 1));
        }
    }
    return ret;
}

int main() {
    int n, m;
    int s, a, b;
    scanf("%d%d%d%d%d", &n, &m, &s, &a, &b);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    memset(dist, INF, sizeof(dist));
    bfs(a, 0); bfs(b, 1);
    printf("%d\n", dfs(s, 0));        
    return 0;
}
