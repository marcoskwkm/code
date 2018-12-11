// Directed weighted graph
template<class WTYPE> struct WeightedGraph {
    int V;
    vector<vector<pair<int, WTYPE>>> adj;

    WeightedGraph(int _V) : V(_V) { adj.resize(V); }

    void add_edge(int u, int v, WTYPE w) {
        adj[u].push_back(make_pair(v, w));
    }
};
