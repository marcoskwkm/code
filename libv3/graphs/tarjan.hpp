template<class EType> struct Tarjan {
    vector<int> comp_id;
    vector<vector<int>> comps;

    Graph<EType> &g;
    vector<int> ind, low;
    vector<bool> in_stack;
    stack<int> st;
    int pre;

    Tarjan(Graph<EType> &_g) : g(_g) {
        comp_id.resize(g.V);
        ind.resize(g.V, -1);
        low.resize(g.V);
        in_stack.resize(g.V);
        pre = 0;

        for (int v = 0; v < g.V; v++) {
            if (ind[v] == -1) {
                dfs(v);
            }
        }
    }

    Graph<Edge> get_contracted_graph() {
        set<pair<int, int>> seen;
        Graph<Edge> cg(comps.size());
        for (int u = 0; u < g.V; u++) {
            for (auto edge: g.adj[u]) {
                if (comp_id[u] != comp_id[edge->v]) {
                    if (seen.find({comp_id[u], comp_id[edge->v]}) == seen.end()) {
                        seen.insert({comp_id[u], comp_id[edge->v]});
                        Edge::add(cg, comp_id[u], comp_id[edge->v]);
                    }
                }
            }
        }
        return cg;
    }

  private:
    void dfs(int v) {
        ind[v] = low[v] = pre++;
        st.push(v);
        in_stack[v] = 1;
        for (auto edge: g.adj[v]) {
            if (ind[edge->v] == -1) {
                dfs(edge->v);
                low[v] = min(low[v], low[edge->v]);
            } else if (in_stack[edge->v]) {
                low[v] = min(low[v], ind[edge->v]);
            }
        }
        if (ind[v] == low[v]) {
            vector<int> cmp;
            int vv;
            do {
                vv = st.top();
                st.pop();
                in_stack[vv] = 0;
                comp_id[vv] = comps.size();
                cmp.push_back(vv);
            } while (vv != v);
            comps.push_back(cmp);
        }
    }
};
