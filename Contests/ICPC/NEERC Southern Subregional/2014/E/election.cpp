#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)2e5 + 10;

int m[MAXN], r[MAXN];

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
    int n;
    cin >> n;
    int n_win = 0;
    FlowGraph g(n + 2);
    int s = n, t = n + 1;
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &m[i], &r[i]);
        if (m[i] > r[i]) n_win++;
        if (i & 1) g.add_edge(i, t, 1);
        else g.add_edge(s, i, 1);
    }
    for (int i = 0; i + 1 < n; i++) {
        int u = i, v = i + 1;
        if (m[u] - r[u] < m[v] - r[v]) swap(u, v);
        if ((m[u] > r[u] && m[v] <= r[v] && m[u] + m[v] > r[u] + r[v]) ||
            m[u] <= r[u]) {
            if (i & 1) g.add_edge(i + 1, i, 1);
            else g.add_edge(i, i + 1, 1);
        }
    }
    int needs = max(0, n - (2 * n_win - 1));
    Dinic mf(g);
    int got = mf.max_flow(s, t);
    if (got < needs) printf("-1\n");
    else {
        printf("%d\n", needs);
        int cnt = 0;
        for (int i = 0; i < n && cnt < needs; i += 2) {
            for (int idx: g.adj[i]) {
                if (g.edges[idx].cap == 0 && g.edges[idx].v != s) {
                    cnt++;
                    printf("%d %d\n", i + 1, g.edges[idx].v + 1);
                }
            }
        }
    }        
    return 0;
}
