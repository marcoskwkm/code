#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 410;

int dist[2][MAXN][MAXN][MAXN];
vector<pii> adj[MAXN];
int t[MAXN];
int tempOrder[MAXN];
int posHigh[MAXN], posLow[MAXN];

int main() {
    int n, m;
    cin >> n >> m;
    set<int> temps;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &t[i]);
        tempOrder[i] = i;
        temps.insert(t[i]);
    }
    
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        adj[u].push_back(pii(v, w));
        adj[v].push_back(pii(u, w));
    }

    sort(tempOrder + 1, tempOrder + n + 1, [](int a, int b) {
        return t[a] < t[b];
    });

    int tCnt = 1;
    int pos = 1;
    for (int temp: temps) {
        while (pos + 1 <= n && t[tempOrder[pos + 1]] <= temp)
            pos++;
        posLow[tCnt++] = pos;
    }
    while (tCnt <= n)
        posLow[tCnt++] = n;
    tCnt = 1, pos = 1;
    for (auto it = temps.rbegin(); it != temps.rend(); it++) {
        while (pos + 1 <= n && t[tempOrder[n + 1 - pos - 1]] >= *it)
            pos++;
        posHigh[tCnt++] = pos;
    }
    while (tCnt <= n)
        posHigh[tCnt++] = n;
    
    memset(dist[0][0], INF, sizeof(dist[0][0]));
    memset(dist[1][0], INF, sizeof(dist[1][0]));
    for (int i = 1; i <= n; i++) {
        dist[0][0][i][i] = dist[1][0][i][i] = 0;
        for (pii edge: adj[i]) {
            dist[0][0][i][edge.first] = dist[1][0][i][edge.first] = edge.second;
        }
    }

    for (int k = 1; k <= n; k++) {
        int w = tempOrder[k], w2 = tempOrder[n + 1 - k];
        for (int u = 1; u <= n; u++) {
            for (int v = 1; v <= n; v++) {                
                dist[0][k][u][v] = min(dist[0][k - 1][u][v], dist[0][k - 1][u][w] + dist[0][k - 1][w][v]);
                dist[1][k][u][v] = min(dist[1][k - 1][u][v], dist[1][k - 1][u][w2] + dist[1][k - 1][w2][v]);
            }
        }
    }

    int q;
    for (cin >> q; q--;) {
        int u, v, k, tt;
        scanf("%d%d%d%d", &u, &v, &k, &tt);
        if (tt == 0) {
            int kk = posLow[k];
            printf("%d\n", dist[0][kk][u][v] == INF ? -1 : dist[0][kk][u][v]);
        } else {
            int kk = posHigh[k];
            printf("%d\n", dist[1][kk][u][v] == INF ? -1 : dist[1][kk][u][v]);
        }
    }                
    return 0;
}
