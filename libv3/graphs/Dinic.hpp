template<class EType> struct Dinic {
    using FType = typename EType::FType;
    vector<int> ptr, dist;
    Graph<EType> &g;

    Dinic(Graph<EType> &_g) : g(_g) {
        ptr.resize(g.V);
        dist.resize(g.V);
    }

    bool bfs(int s, int t) {
        fill(dist.begin(), dist.end(), -1);
        dist[s] = 0;
        queue<int> q({s});
        while (!q.empty()) {
            int v = q.front();
            if (dist[v] == dist[t])
                break;
            q.pop();
            for (const auto edge: g.adj[v]) {
                if (dist[edge->v] == -1 && edge->cap) {
                    dist[edge->v] = dist[v] + 1;
                    q.push(edge->v);
                }
            }
        }
        return dist[t] != -1;
    }

    FType dfs(int v, int t, FType flow) {
        if (v == t) {
            return flow;
        }
        for (int &p = ptr[v]; p < (int)g.adj[v].size(); p++) {
            auto edge = g.adj[v][p];
            if (dist[edge->v] == dist[v] + 1 && edge->cap) {
                FType got = dfs(edge->v, t, min(flow, edge->cap));
                if (got) {
                    edge->cap -= got;
                    edge->rev->cap += got;
                    return got;
                }
            }
        }
        return 0;
    }

    FType max_flow(int s, int t) {
        FType ret = 0;
        while (bfs(s, t)) {
            fill(ptr.begin(), ptr.end(), 0);
            while (FType got = dfs(s, t, numeric_limits<FType>::max()))
                ret += got;
        }
        return ret;
    }
};
