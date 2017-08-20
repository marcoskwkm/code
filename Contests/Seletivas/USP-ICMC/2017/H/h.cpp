#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 1010, MAXK = 510;

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

int gain[MAXK][MAXK];
int pies[MAXN];
bool can_eat[2][MAXK];
int w[MAXN];

int main() {
    int k, n, na, nb;
    cin >> k >> n >> na >> nb;
    for (int i = 0; i < na; i++) {
        int x;
        scanf("%d", &x);
        can_eat[0][x - 1] = 1;
    }
    for (int i = 0; i < nb; i++) {
        int x;
        scanf("%d", &x);
        can_eat[1][x - 1] = 1;
    }
    for (int i = 0; i < n; i++)
        scanf("%d", &pies[i]);
    for (int i = 0; i + 1 < n; i++)
        scanf("%d", &w[i]);
    for (int i = 0; i + 1 < n; i++) {
        int k1 = pies[i] - 1, k2 = pies[i + 1] - 1;
        gain[k1][k2] += w[i];
        if (k1 != k2) gain[k2][k1] += w[i];
    }

    lint ans = 0;
    FlowGraph g(k + 2);
    int s = k, t = k + 1;
    for (int i = 0; i < k; i++) {
        if (!can_eat[1][i]) {
            g.add_edge(s, i, INF);
            ans += gain[i][i];
        }
        else if (!can_eat[0][i]) {
            g.add_edge(i, t, INF);
            ans += gain[i][i];
        }
        else {
            g.add_edge(s, i, gain[i][i]);
            g.add_edge(i, t, gain[i][i]);
            ans += 2 * gain[i][i];
        }            
        for (int j = i + 1; j < k; j++) {
            g.add_edge(i, j, gain[i][j]);
            g.add_edge(j, i, gain[i][j]);
            ans += gain[i][j];
        }
    }

    Dinic mf(g);
    ans -= mf.max_flow(s, t);
    cout << ans << endl;
}
