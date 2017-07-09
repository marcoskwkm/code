#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;

int dist[MAXN], d[MAXN];
vector<int> adj[MAXN];

int main() {
    #ifndef HOME
    freopen("jumping.in", "r", stdin);
    #endif

    int t;
    for (scanf("%d", &t); t--;) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            adj[i].clear();
        for (int i = 0; i < n; i++) {
            scanf("%d", &d[i]);
            if (i + d[i] < n) adj[i + d[i]].push_back(i);
            if (i - d[i] >= 0) adj[i - d[i]].push_back(i);
        }
        queue<int> fila;
        fila.push(n - 1);
        memset(dist, -1, sizeof(dist));
        dist[n - 1] = 0;
        while (!fila.empty()) {
            int v = fila.front();
            fila.pop();
            for (int nxt: adj[v]) {
                if (dist[nxt] == -1) {
                    dist[nxt] = dist[v] + 1;
                    fila.push(nxt);
                }
            }
        }
        for (int i = 0; i < n; i++)
            printf("%d\n", dist[i]);
    }        
    return 0;
}
