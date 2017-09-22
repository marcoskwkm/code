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


/* 
   Computes a Gomory-Hu tree of a given connected undirected graph.
   Any minimum cut (S, T) in the tree is also a minimum cut in the original
   graph.   
*/
template<class FTYPE, template<class> class MF> struct GomoryHuTree {
    WeightedGraph tree;
    
    FlowGraph<FTYPE> &g;
    
    GomoryHuTree(FlowGraph<FTYPE> &_g) : g(_g) {
        vector<int> parent(g.V, 0), depth(g.V, 0);
        vector<FTYPE> cap;
        for (int s = 1; s < g.V; s++) {
            int t = parent[s];
            FlowGraph<FTYPE> g2 = g;
            MF mf(g2);
            int fst = mf.max_flow(s, t);
            cap[s] = fst;
            vector<boo> in_cut(g.V, 0);
            queue<int> q({s});
            in_cut[s] = 1;
            while (!q.empty()) {
                int v = q.front();
                q.pop();
                for (int i: g2.adj[v]) {
                    int nxt = g2.edges[i].v;
                    if (g2.edges[i].cap > 0 && !in_cut[nxt]) {
                        in_cut[nxt] = 1;
                        q.push(nxt);
                    }
                }
            }
            for (int v = 0; v < g.V; v++)
                if (v != s && in_cut[v] && parent[v] == t)
                    parent[v] = s;
            if (in_cut[parent[t]]) {
                parent[s] = parent[t];
                parent[t] = s;
                cap[s] = cap[t];
                cap[t] = fst;
            }
        }
        for (int v = 1; v < g.V; v++) {
            tree.
            
    }
};    

int main() {
    FlowGraph<lint> g(2);
    g.add_edge(0, 1, 100000);
    GomoryHuTree<lint, Dinic> tree(g);
    return 0;
}
