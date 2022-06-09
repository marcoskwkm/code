template<class EType> struct Dijkstra {
    using WType = typename EType::WType;
    Graph<EType> &g;

    Dijkstra(Graph<EType> &_g) : g(_g) {}

    vector<WType> run(int s) {
        vector<WType> dist(g.V, -1);
        set<pair<WType, int>> pq = {{0, s}};
        dist[s] = 0;

        while (!pq.empty()) {
            auto [d, v] = *pq.begin();
            pq.erase(pq.begin());

            for (auto edge: g.adj[v]) {
                WType new_d = d + edge->w;
                if (dist[edge->v] == -1 || dist[edge->v] > new_d) {
                    pq.erase({dist[edge->v], edge->v});
                    dist[edge->v] = new_d;
                    pq.insert({dist[edge->v], edge->v});
                }
            }
        }

        return dist;
    }
};
