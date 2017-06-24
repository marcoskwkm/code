#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

/* Data structure to represent a network flow graph */
struct FlowGraph {
    struct Edge {
        int v, cap;
        Edge(int _v, int _cap) : v(_v), cap(_cap) {}
    };

    int V;
    vector<Edge> edges;
    vector<vector<int>> adj;

    FlowGraph(int _V) : V(_V) {
        adj.resize(V);
    }

    void add_edge(int u, int v, int cap) {
        adj[u].push_back(edges.size());
        edges.push_back(Edge(v, cap));
        adj[v].push_back(edges.size());
        edges.push_back(Edge(u, 0));
    }
};

/*
  Dinic maxflow algorithm - O(EV^2)
  O(EV^(2/3)) for unit capacities
  O(EV^(1/2)) for bipartite graphs
*/
struct Dinic {
    vector<int> ptr, dist;
    FlowGraph &g;

    Dinic(FlowGraph &_g) : g(_g) {
        ptr.resize(g.V);
        dist.resize(g.V);
    }

    bool bfs(int s, int t) {
        fill(dist.begin(), dist.end(), -1);
        dist[s] = 0;
        queue<int> q({s});
        while (!q.empty()) {
            int v = q.front();
            if (dist[v] == dist[t]) break;
            q.pop();
            for (int i: g.adj[v]) {
                int nxt = g.edges[i].v;
                if (dist[nxt] == -1 && g.edges[i].cap) {
                    dist[nxt] = dist[v] + 1;
                    q.push(nxt);
                }
            }
        }
        return dist[t] != -1;
    }

    int dfs(int v, int t, int flow) {
        if (v == t) return flow;
        for (int &p = ptr[v]; p < (int)g.adj[v].size(); p++) {
            int i = g.adj[v][p];
            int nxt = g.edges[i].v;
            if (dist[nxt] == dist[v] + 1 && g.edges[i].cap) {
                int got = dfs(nxt, t, min(flow, g.edges[i].cap));
                if (got) {
                    g.edges[i].cap -= got;
                    g.edges[i^1].cap += got;
                    return got;
                }
            }
        }
        return 0;
    }

    int max_flow(int s, int t) {
        int ret = 0;
        while (bfs(s, t)) {
            fill(ptr.begin(), ptr.end(), 0);
            while (int got = dfs(s, t, INF)) ret += got;
        }
        return ret;
    }
};

const int MAXN = 110;

int v[MAXN];
char type[MAXN];

bool check(int k, int n, int d) {
    FlowGraph g(2*n + 2);
    int s = 2*n, t = 2*n + 1;
    for (int i = 0; i < n; i++) {
        g.add_edge(2*i, 2*i + 1, type[i] == 'S' ? 1 : 2);
        if (v[i] <= k) g.add_edge(s, 2*i, 2);
        if (d - v[i] <= k) g.add_edge(2*i + 1, t, 2);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            if (0 < v[j] - v[i] && v[j] - v[i] <= k)
                g.add_edge(2*i + 1, 2*j, 2);
        }
    }
    Dinic mf(g);
    return mf.max_flow(s, t) >= 2;
}    

int main() {
    int t = 1, T;
    for (scanf("%d", &T); t <= T; t++) {
        int n, d;
        scanf("%d%d", &n, &d);
        for (int i = 0; i < n; i++)
            scanf(" %c%*c%d", &type[i], &v[i]);
        int l = 1, r = d;
        while (l < r) {
            int mid = (l + r) / 2;
            if (check(mid, n, d)) r = mid;
            else l = mid + 1;
        }
        printf("Case %d: %d\n", t, l);
    }        
    return 0;
}
