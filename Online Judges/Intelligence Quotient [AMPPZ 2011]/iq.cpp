/*
  Solucao do problema Intelligence Quotient
  Complexidade: O(N * M * sqrt(N + M))
*/

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

    lint max_flow(int s, int t) {
        lint ret = 0;
        while (bfs(s, t)) {
            fill(ptr.begin(), ptr.end(), 0);
            while (int got = dfs(s, t, INF)) ret += got;
        }
        return ret;
    }
};

const int MAXN = 410;

bool knows[MAXN][MAXN]; // verdadeiro se 'a' conhece 'b'
bool seen[2 * MAXN];

void dfs(int v, FlowGraph &g) {
    seen[v] = 1;
    for (int idx: g.adj[v]) {
        int nxt = g.edges[idx].v;
        if (!seen[nxt] && g.edges[idx].cap > 0)
            dfs(nxt, g);
    }
}            

int main() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    FlowGraph g(n + m + 2);
    int s = n + m, t = n + m + 1;
    for (int i = 0; i < k; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        knows[a - 1][b - 1] = 1;
    }
    for (int a = 0; a < n; a++)
        for (int b = 0; b < m; b++)
            if (!knows[a][b])
                g.add_edge(a, b + n, INF);
    lint total_iq = 0;
    for (int a = 0; a < n; a++) {
        int iq;
        scanf("%d", &iq);
        g.add_edge(s, a, iq);
        total_iq += iq;
    }
    for (int b = 0; b < m; b++) {
        int iq;
        scanf("%d", &iq);
        g.add_edge(b + n, t, iq);
        total_iq += iq;
    }
    Dinic mf(g);
    printf("%lld\n", total_iq - mf.max_flow(s, t));
    dfs(s, g);
    vector<int> sol_a, sol_b;
    for (int a = 0; a < n; a++)
        if (seen[a])
            sol_a.push_back(a + 1);
    for (int b = 0; b < m; b++)
        if (!seen[b + n])
            sol_b.push_back(b + 1);
    printf("%lu\n", sol_a.size());
    for (size_t i = 0; i < sol_a.size(); i++)
        printf("%d ", sol_a[i]);
    printf("\n%lu\n", sol_b.size());
    for (size_t i = 0; i < sol_b.size(); i++)
        printf("%d ", sol_b[i]);
    printf("\n");
    return 0;
}
