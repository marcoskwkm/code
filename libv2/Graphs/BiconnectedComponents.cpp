struct BiconnectedComponents {
    vector<vector<int>> components;

    const Graph &g;
    vector<int> ind, low;
    stack<pii> edges;
    vector<int> last;

    BiconnectedComponents(const Graph &_g) : g(_g) {
        ind.resize(g.V, -1), low.resize(g.V), last.resize(g.V, -1);
        for (int v = 0; v < g.V; v++) {
            if (g.adj[v].empty()) components.push_back({v});
            else if (ind[v] == -1) {
                dfs(v, -1);
                proc_component(-1, -1);
            }
        }
    }

    void dfs(int v, int prv) {
        static int cnt = 0;
        ind[v] = low[v] = cnt++;
        int q = 0;
        for (int nxt: g.adj[v]) {
            if (ind[nxt] == -1) {
                edges.push(pii(v, nxt));
                ++q;
                dfs(nxt, v);
                low[v] = min(low[v], low[nxt]);
                if (prv == -1 && q > 1)
                    proc_component(v, nxt);
                else if (prv != -1 && low[nxt] >= ind[v])
                    proc_component(v, nxt);
            }
            else if (nxt != prv && ind[nxt] < low[v]) {
                edges.push(pii(v, nxt));
                low[v] = ind[nxt];
            }
        }
    }

    void proc_component(int u, int v) {
        vector<int> component;
        while (!edges.empty()) {
            int uu, vv;
            tie(uu, vv) = edges.top();
            edges.pop();
            if (last[uu] != (int)components.size()) {
                last[uu] = components.size();
                component.push_back(uu);
            }
            if (last[vv] != (int)components.size()) {
                last[vv] = components.size();
                component.push_back(vv);
            }
            if (uu == u && vv == v) break;
        }
        components.push_back(component);
    }
};
