#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 410;

vector<int> adj[MAXN];
vector<int> v1d[MAXN];
int dist[MAXN][MAXN];
double p2d[MAXN];
double mostp[MAXN];
double pv[MAXN];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    memset(dist, INF, sizeof(dist));
    for(int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
        dist[u][v] = dist[v][u] = 1;
    }
    for (int v = 1; v <= n; v++) dist[v][v] = 0;
    for (int k = 1; k <= n; k++)
        for (int u = 1; u <= n; u++)
            for (int v = 1; v <= n; v++)
                dist[u][v] = min(dist[u][v], dist[u][k] + dist[k][v]);
    
    for (int v1 = 1; v1 <= n; v1++) {
        double prob_v1 = 0;
        for (int i = 0; i < n; i++) v1d[i].clear();
        for (int v = 1; v <= n; v++) v1d[dist[v1][v]].push_back(v);
        for (int d = 0; d < n; d++) {
            if (v1d[d].empty()) continue;
            double prob1 = 1. / v1d[d].size();
            double prob2 = 0;
            int bestv2 = -1;
            for (int v2 = 1; v2 <= n; v2++) {
                double probv2 = 0;
                memset(pv, 0, sizeof(pv));
                memset(p2d, 0, sizeof(p2d));
                memset(mostp, 0, sizeof(mostp));
                for (int u: v1d[d])
                    for (int nxt: adj[u])
                        pv[nxt] += 1./ adj[u].size() / v1d[d].size();
                for (int v = 1; v <= n; v++) {
                    mostp[dist[v2][v]] = max(mostp[dist[v2][v]], pv[v]);
                    p2d[dist[v2][v]] += pv[v];
                }

                for (int d2 = 0; d2 < n; d2++) {
                    if (p2d[d2] == 0) continue;
                    probv2 += mostp[d2];
                }
                if (probv2 > prob2) {
                    prob2 = probv2;
                    bestv2 = v2;
                }
            }
            if (prob1 > prob2) {
                printf("%d, dist %d: %.3f (Use just once)\n", v1, d, prob1);
                prob_v1 += double(v1d[d].size()) / n * prob1;
            }
            else {
                printf("%d, dist %d: %.3f (Use again on %d)\n", v1, d, prob2, bestv2);
                prob_v1 += double(v1d[d].size()) / n * prob2;
            }
        }
        printf("Answer for %d: %.3f\n", v1, prob_v1);
    }    
    return 0;
}
