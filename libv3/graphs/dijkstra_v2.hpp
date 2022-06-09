template<class EType> struct Dijkstra {
    using WType = typename WeightedEdge::WType;
    Graph<EType> &g;

    Dijkstra(Graph<EType> &_g) : g(_g) {}

    vector<WType> run(int s) {
        vector<WType> dist(g.V, -1);
        vector<bool> done(g.V, 0);
        dist[s] = 0;

        while (1) {
            int cur = -1;
            WType d = -1;

            for (int v = 0; v < g.V; v++) {
                if (done[v] || dist[v] == -1) {
                    continue;
                }

                if (cur == -1 || dist[v] < d) {
                    d = dist[v];
                    cur = v;
                }
            }

            if (cur == -1) {
                break;
            }

            for (auto edge: g.adj[cur]) {
                WType new_d = d + edge->w;
                if (dist[edge->v] == -1 || dist[edge->v] > new_d) {
                    dist[edge->v] = new_d;
                }
            }

            done[cur] = 1;
        }

        return dist;
    }
};
