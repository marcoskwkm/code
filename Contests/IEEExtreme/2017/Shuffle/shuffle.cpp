#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

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
    int n;
    cin >> n;
    FlowGraph<int> g(2*n + 2);
    int s = 2*n, t = 2*n + 1;
    for (int i = 0; i < n; i++) {
        g.add_edge(s, i, 1);
        g.add_edge(i + n, t, 1);
    }
    
    string line;
    getline(cin, line);
    for (int i = 0; i < n; i++) {
        getline(cin, line);
        stringstream ss(line);
        set<int> lodges({i});
        int x;
        while (ss >> x) lodges.insert(x);
        for (int j = 0; j < n; j++)
            if (lodges.find(j) == lodges.end())
                g.add_edge(i, j + n, 1);
    }
    Dinic<int> mf(g);
    printf("%d\n", n - mf.max_flow(s, t));        
    return 0;
}
