#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 110;

int rows[MAXN], cols[MAXN];
vector<pii> costumes[2 * MAXN];
int grid[MAXN][MAXN];

/* Data structure to represent a network flow graph */
template<class FTYPE> struct FlowGraph {
    struct Edge {
        int v;
        FTYPE cap;
        Edge(int _v, FTYPE _cap) : v(_v), cap(_cap) {}
    };

    int V;
    vector<Edge> edges;
    vector<vector<int>> adj;

    FlowGraph(int _V) : V(_V) { adj.resize(V); }

    void add_edge(int u, int v, FTYPE cap) {
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
template<class FTYPE> struct Dinic {
    vector<int> ptr, dist;
    FlowGraph<FTYPE> &g;

    Dinic(FlowGraph<FTYPE> &_g) : g(_g) {
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

    FTYPE dfs(int v, int t, FTYPE flow) {
        if (v == t) return flow;
        for (int &p = ptr[v]; p < (int)g.adj[v].size(); p++) {
            int i = g.adj[v][p];
            int nxt = g.edges[i].v;
            if (dist[nxt] == dist[v] + 1 && g.edges[i].cap) {
                FTYPE got = dfs(nxt, t, min(flow, g.edges[i].cap));
                if (got) {
                    g.edges[i].cap -= got;
                    g.edges[i^1].cap += got;
                    return got;
                }
            }
        }
        return 0;
    }

    FTYPE max_flow(int s, int t) {
        FTYPE ret = 0;
        while (bfs(s, t)) {
            fill(ptr.begin(), ptr.end(), 0);
            while (FTYPE got = dfs(s, t, numeric_limits<FTYPE>::max()))
                ret += got;
        }
        return ret;
    }
};


int main() {
    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        int n;
        scanf("%d", &n);
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                int cost;
                scanf("%d", &cost);
                if (cost < 0) cost = n - cost;
                grid[r][c] = cost;
                costumes[cost].push_back(pii(r, c));
            }
        }
        int ans = 0;
        for (int i = 1; i <= 2 * n; i++) {
            memset(rows, 0, sizeof(rows));
            memset(cols, 0, sizeof(cols));
            FlowGraph<int> g(2 * n + 2);
            for (pii p: costumes[i]) {
                rows[p.first]++;
                cols[p.second]++;
                g.add_edge(p.first, n + p.second, 1);
            }
            int sr = 0, sc = 0;
            for (int j = 0; j < n; j++) {
                sr += max(0, rows[j] - 1);
                sc += max(0, cols[j] - 1);
            }
            int src = 2 * n, snk = 2 * n + 1;
            for (int j = 0; j < n; j++) {
                if (rows[j] > 1) g.add_edge(src, j, rows[j] - 1);
                if (cols[j] > 1) g.add_edge(n + j, snk, cols[j] - 1);
            }
            Dinic<int> dinic(g);
            ans += sr + sc - dinic.max_flow(src, snk);
            costumes[i].clear();
        }
        printf("Case #%d: %d\n", t, ans);
    }                
    return 0;
}
