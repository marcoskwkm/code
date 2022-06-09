struct WeightedEdge {
    using WType = int;
    static const int MAX_EDGES = (int)1e7;
    static int edge_cnt;
    static array<WeightedEdge, MAX_EDGES> edges;

    int v;
    WType w;

    WeightedEdge() {}
    WeightedEdge(int _v, WType _w) : v(_v), w(_w) {}

    static void add(Graph<WeightedEdge> &g, int u, int v, WType w) {
        edges[edge_cnt++] = WeightedEdge(v, w);
        g.adj[u].push_back(&edges[edge_cnt - 1]);
    }
};

int WeightedEdge::edge_cnt = 0;
array<WeightedEdge, WeightedEdge::MAX_EDGES> WeightedEdge::edges;
