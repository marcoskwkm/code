namespace bap {
    int ind[MAXN], low[MAXN];
    int cnt;
    
    void bap_dfs(int v, int prev = -1) {
        ind[v] = low[v] = cnt++;
        int cont = 0;
        bool flag = 0;
        for (int nxt: adj[v]) {
            if (ind[nxt] == -1) {
                ++cont;
                bap_dfs(nxt, v);
                low[v] = min(low[v], low[nxt]);
                if (low[nxt] >= ind[v]) flag = 1;
                if (low[nxt] == ind[nxt]) {
                    // v-nxt is a bridge
                }
            }
            else if (nxt != prev) low[v] = min(low[v], ind[nxt]);
        }
        if(prev == -1) {
            if(cont > 1) {
                // v is an articulation point
            }
        }
        else if(flag) {
            // v is an articulation point
        }
    }

    void init() {
        memset(ind, -1, sizeof(ind));
        cnt = 0;
    }
}
