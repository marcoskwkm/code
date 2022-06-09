struct FlowEdge {
    using FType = int;
    static const int MAX_EDGES = (int)1e7;
    static int edge_cnt;
    static array<FlowEdge, MAX_EDGES> edges;

    int v;
    FType cap;
    FlowEdge *rev;

    FlowEdge() {}
    FlowEdge(int _v, FType _cap) : v(_v), cap(_cap), rev(NULL) {}

    static void add(Graph<FlowEdge> &g, int u, int v, FType cap) {
        edges[edge_cnt++] = FlowEdge(v, cap);
        edges[edge_cnt++] = FlowEdge(u, 0);
        auto uv = &edges[edge_cnt - 2];
        auto vu = &edges[edge_cnt - 1];
        uv->rev = vu;
        vu->rev = uv;
        g.adj[u].push_back(uv);
        g.adj[v].push_back(vu);
    }
};

int FlowEdge::edge_cnt = 0;
array<FlowEdge, FlowEdge::MAX_EDGES> FlowEdge::edges;
