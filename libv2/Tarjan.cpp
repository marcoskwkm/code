/* Finds all SCCs in a directed graph */
struct Tarjan {
    vector<int> cmp_id;      // component of each vertex
    vector<vector<int>> cmp; // list of each component

    Graph& g;
    vector<int> ind, low;
    vector<bool> in_stack;
    stack<int> st;
    int pre;

    Tarjan(Graph _g) : g(_g) {
        cmp_id.resize(g.V);
        ind.resize(g.V, -1);
        low.resize(g.V);
        in_stack.resize(g.V);
        pre = 0;
        for (int v = 0; v < g.V; v++) {
            if (ind[v] == -1)
                dfs(v);
        }
    }

    void dfs(int v) {
        ind[v] = low[v] = pre++;
        st.push(v);
        in_stack[v] = 1;
        for (int nxt: g.adj[v]) {
            if (ind[nxt] == -1) {
                dfs(nxt);
                low[v] = min(low[v], low[nxt]);
            }
            else if (in_stack[nxt]) {
                low[v] = min(low[v], ind[nxt]);
            }
        }
        if (ind[v] == low[v]) {
            vector<int> component;
            int vv;
            do {
                vv = st.top();
                st.pop();
                in_stack[vv] = 0;
                cmp_id[vv] = cmp.size();
                component.push_back(vv);
            } while (vv != v);
            cmp.push_back(component);
        }
    }
};
