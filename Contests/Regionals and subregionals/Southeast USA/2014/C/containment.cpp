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

    FlowGraph(int _V) : V(_V) { adj.resize(V); }

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

int main() {
    int nt;
    for (cin >> nt; nt--;) {
        FlowGraph g(1000 + 2);
        int s = 1000, t = 1001;
        int n;
        for (scanf("%d", &n); n--;) {
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            g.add_edge(100*x + 10*y + z, t, INF);
        }
        for (int x = 0; x < 10; x++) {
            for (int y = 0; y < 10; y++) {
                for (int z = 0; z < 10; z++) {
                    int id = 100*x + 10*y + z;
                    if (x == 0) g.add_edge(s, id, 1);
                    if (x == 9) g.add_edge(s, id, 1);
                    if (y == 0) g.add_edge(s, id, 1);
                    if (y == 9) g.add_edge(s, id, 1);
                    if (z == 0) g.add_edge(s, id, 1);
                    if (z == 9) g.add_edge(s, id, 1);
                    for (int d = -1; d <= 1; d += 2) {
                        int nx = x + d, ny = y, nz = z;
                        if (!(nx < 0 || ny < 0 || nz < 0 || nx > 9 || ny > 9 || nz > 9))
                            g.add_edge(id, 100*nx + 10*ny + nz, 1);
                        nx = x, ny = y + d, nz = z;
                        if (!(nx < 0 || ny < 0 || nz < 0 || nx > 9 || ny > 9 || nz > 9))
                            g.add_edge(id, 100*nx + 10*ny + nz, 1);
                        nx = x, ny = y, nz = z + d;
                        if (!(nx < 0 || ny < 0 || nz < 0 || nx > 9 || ny > 9 || nz > 9))
                            g.add_edge(id, 100*nx + 10*ny + nz, 1);
                    }
                }
            }
        }
        Dinic mf(g);
        printf("%d\n", mf.max_flow(s, t));
    }
    return 0;
}
