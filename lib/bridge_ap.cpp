// Bridge and Articulation Point - O(V+E)
// Precisa de adj[MAXN][MAXN] e deg[MAXN] (lista de adj)
// Teste: SPOJ SUBMERGE (MANUT tem casos fracos!)
 
int ind[MAXN],low[MAXN]; // Zerar ind com -1! <-----------------
int cnt;                 // Zerar!            <-----------------

// Chamar com prev = -1
void bap_dfs(int v,int prev) {
    ind[v] = low[v] = cnt++;
    int cont = 0;
    bool flag = 0;
    for(int a=0;a<adj[v].size();++a) {
        int nxt = adj[v][a];
        if(ind[nxt] == -1) {
            ++cont;
            bap_dfs(nxt,v);
            low[v] = min(low[v],low[nxt]);
            if(low[nxt] >= ind[v]) flag = 1;
            if(low[nxt] == ind[nxt]) {
                // v-nxt eh uma ponte
            }
        }
        else if(nxt != prev) low[v] = min(low[v],ind[nxt]);
    }
    if(prev == -1) {
        if(cont > 1) {
            // v eh um ponto de articulacao
        }
    }
    else if(flag) {
        // v eh um ponto de articulacao
    }
}
