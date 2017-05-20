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

namespace EdmondsKarp {
    const int INF = 0x3f3f3f3f;

    int augment(int s, int t, FlowGraph &g) {
        vector<int> prv(g.V, -1), flow(g.V, INF);
        prv[s] = s;
        queue<int> q({s});
        while (!q.empty() && prv[t] == -1) {
            int v = q.front();
            q.pop();
            for (int i: g.adj[v]) {
                if (prv[g.edges[i].v] == -1 && g.edges[i].cap) {
                    prv[g.edges[i].v] = i;
                    flow[g.edges[i].v] = min(flow[v], g.edges[i].cap);
                    q.push(g.edges[i].v);
                }
            }
        }
        if (prv[t] == -1) return 0;
        for (int v = t; v != s; v = g.edges[prv[v]^1].v) {
            g.edges[prv[v]].cap -= flow[t];
            g.edges[prv[v]^1].cap += flow[t];
        }
        return flow[t];
    }

    int max_flow(int s, int t, FlowGraph &g) {
        int total_flow = 0;
        while (int flow = augment(s, t, g)) total_flow += flow;
        return total_flow;
    }
}

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        int n;
        scanf("%d", &n);
        FlowGraph g(n + 1);
        for (int u = 1; u < n; u++) {
            int q;
            for (scanf("%d", &q); q--;) {
                int v;
                scanf("%d", &v);
                g.add_edge(u, v, (u == 1 || v == n) ? 1 : INF);
            }
        }
        cout << EdmondsKarp::max_flow(1, n, g) << endl;
    }        
    return 0;
}
