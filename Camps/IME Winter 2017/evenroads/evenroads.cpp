#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e4 + 10;

vector<pii> adj[MAXN];
lint dist[2 * MAXN];

void dijkstra(int s) {
    memset(dist, INF, sizeof(dist));
    dist[s] = 0;
    set<pll> pq;
    pq.insert(pll(0, s));
    while (!pq.empty()) {
        int v = pq.begin()->second;
        lint d = dist[v];
        int p = v & 1;
        v /= 2;
        pq.erase(pq.begin());
        for (pii edge: adj[v]) {
            int nxt = 2*edge.first + (p^1);
            if (dist[nxt] > d + edge.second) {
                pq.erase(pll(dist[nxt], nxt));
                dist[nxt] = d + edge.second;
                pq.insert(pll(dist[nxt], nxt));
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        u--, v--;
        adj[u].push_back(pii(v, c));
        adj[v].push_back(pii(u, c));
    }
    dijkstra(0);
    printf("%lld\n", dist[2*n - 2] == LINF ? -1 : dist[2*n - 2]);    
    return 0;
}
