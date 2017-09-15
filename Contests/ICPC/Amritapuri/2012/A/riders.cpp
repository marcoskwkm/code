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

const int MAXN = 110;
int w[MAXN][MAXN];

int main() {
    int nt;
    for (scanf("%d", &nt); nt--;) {
        int n, m, k, th;
        scanf("%d%d%d%d", &n, &m, &k, &th);
        for (int r = 0; r < n; r++)
            for (int c = 0; c < m; c++)
                scanf("%d", &w[r][c]);
        int l = 0, r = (int)2e7 + 10;
        while (l < r) {
            int mid = (l + r) / 2;
            FlowGraph g(n + 2*m + 2);
            int s = n + 2*m, t = n + 2*m + 1;
            for (int i = 0; i < n; i++)
                g.add_edge(s, i, 1);
            for (int i = 0; i < 2*m; i++)
                g.add_edge(n + i, t, 1);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (w[i][j] <= mid - th)
                        g.add_edge(i, n + j, 1);
                    if (w[i][j] <= mid)
                        g.add_edge(i, n + m + j, 1);
                }
            }
            Dinic mf(g);
            if (mf.max_flow(s, t) >= k) r = mid;
            else l = mid + 1;
        }
        printf("%d\n", l);
    }        
    return 0;
}
