#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10, MAXM = (int)1e6 + 10;

vector<pii> adj[MAXN];
int dist[MAXN][2];
int N, M, K;

int main() {
    cin >> N >> M >> K;
    for (int i = 0; i < M; i++) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        adj[u].push_back(pii(v, c));
        adj[v].push_back(pii(u, c));
    }

    memset(dist, INF, sizeof(dist));
    set<pii> pq;
    for (int i = 0; i < K; i++) {
        int v;
        scanf("%d", &v);
        dist[v][0] = dist[v][1] = 0;
        pq.insert(pii(0, v));
    }
    while (!pq.empty()) {
        int v = pq.begin()->second;
        pq.erase(pq.begin());
        for (pii edge: adj[v]) {
            int w, cst;
            tie(w, cst) = edge;
            if (dist[v][1] + cst < dist[w][0]) {
                if (dist[w][0] != dist[w][1]) {
                    pq.erase(pii(dist[w][1], w));
                    dist[w][1] = dist[w][0];
                    pq.insert(pii(dist[w][1], w));
                }
                dist[w][0] = dist[v][1] + cst;
            }
            else if (dist[v][1] + cst < dist[w][1]) {
                pq.erase(pii(dist[w][1], w));
                dist[w][1] = dist[v][1] + cst;
                pq.insert(pii(dist[w][1], w));
            }
        }
    }

    cout << dist[0][1] << endl;
    return 0;
}
