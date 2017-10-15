#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<lint, lint, lint> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)2e4 + 10;

template<class WTYPE> struct WeightedGraph {
    int V;
    vector<vector<pair<int, WTYPE>>> adj;

    WeightedGraph(int _V) : V(_V) { adj.resize(V); }

    void add_edge(int u, int v, WTYPE w) {
        adj[u].push_back(make_pair(v, w));
    }
};

pll dist[MAXN];
void dijkstra(int s, const WeightedGraph<pll> &g) {
    for (int i = 0; i < MAXN; i++)
        dist[i] = pll(LINF, LINF);
    dist[s] = pii(0, 0);
    set<tiii> pq({tiii(0, 0, s)});
    while (!pq.empty()) {
        lint d, gd, v;
        tie(d, gd, v) = *pq.begin();
        pq.erase(pq.begin());
        for (auto edge: g.adj[v]) {
            pll nd(d + edge.second.first, gd + edge.second.second);
            int nxt = edge.first;
            if (nd < dist[nxt]) {
                pq.erase(tiii(dist[nxt].first, dist[nxt].second, nxt));
                dist[nxt] = nd;
                pq.insert(tiii(dist[nxt].first, dist[nxt].second, nxt));
            }
        }
    }
}

const vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};

int main() {
    int n, m;
    cin >> n >> m;
    map<lint, int> id;
    map<lint, int> gold;
    for (int i = 0; i < n; i++) {
        lint x;
        scanf("%lld", &x);
        id[x] = i;
        lint p = 1;
        int k = 0;
        while (k < 15 && p * primes[k] <= x) p *= primes[k++];
        gold[x] = k;
    }
    WeightedGraph<pll> g(n);
    for (int i = 0; i < m; i++) {
        lint u, v, d;
        scanf("%lld%lld%lld", &u, &v, &d);
        g.add_edge(id[u], id[v], pll(d, -gold[v]));
        g.add_edge(id[v], id[u], pll(d, -gold[u]));
    }
    dijkstra(id.begin()->second, g);

    printf("%lld\n", -dist[id.rbegin()->second].second + gold.begin()->second);
    return 0;
}
