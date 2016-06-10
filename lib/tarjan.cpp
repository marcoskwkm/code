namespace Tarjan {
    int cmp[MAXN]; // component of [i]
    int cnt;       // number of components
    int ind[MAXN], low[MAXN], pre;
    bool instack[MAXN];
    stack<int> st;

    void tarjan(int v) {
        ind[v] = low[v] = pre++;
        st.push(v);
        instack[v] = 1;
        for (int nxt: adj[v]) {
            if (ind[nxt] == -1) {
                tarjan(nxt);
                low[v] = min(low[v], low[nxt]);
            }
            else if (instack[nxt]) low[v] = min(low[v], ind[nxt]);
        }
        if (ind[v] == low[v]) {
            int vv;
            do {
                vv = st.top();
                st.pop();
                instack[vv] = 0;
                cmp[vv] = cnt;
            } while (vv != v);
            ++cnt;
        }
    }

    inline void init() {
        memset(ind, -1, sizeof(ind));
        pre = 0; cnt = 0;
    }
}
