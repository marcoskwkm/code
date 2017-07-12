/* Data structure to represent a network flow graph with costs */
struct CostFlowGraph {
    struct Edge {
        int v;
        int cap;
        int cst;
        Edge(int _v, int _cap, int _cst) : v(_v), cap(_cap), cst(_cst) {}
    };

    int V;
    vector<Edge> edges;
    vector<vector<int>> adj;

    CostFlowGraph(int _V) : V(_V) { adj.resize(V); }

    void add_edge(int u, int v, int cap, int cst) {
        adj[u].push_back(edges.size());
        edges.push_back(Edge(v, cap, cst));
        adj[v].push_back(edges.size());
        edges.push_back(Edge(u, 0, -cst));
    }
};
