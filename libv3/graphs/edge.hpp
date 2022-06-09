struct Edge {
    static const int MAX_EDGES = (int)1e7;
    static int edge_cnt;
    static array<Edge, MAX_EDGES> edges;

    int v;

    Edge() {}
    Edge(int _v) : v(_v) {}

    static void add(Graph<Edge> &g, int u, int v) {
        edges[edge_cnt++] = Edge(v);
        g.adj[u].push_back(&edges[edge_cnt - 1]);
    }
};

int Edge::edge_cnt = 0;
array<Edge, Edge::MAX_EDGES> Edge::edges;
