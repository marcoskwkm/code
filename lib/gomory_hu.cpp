// Gomory-Hu Tree
// Finds flow-equivalent tree of a graph
// Minimum edge in an s-t path corresponds to the maxflow of s-t and
// divides the tree into two components which represents the s-t cut.
// Uses Gusfield's algorithm: Performs V - 1 maxflows
// Requires: dinic

const int LOG = 20;

int cut[MAXV], up[LOG][MAXV], val[LOG][MAXV];
int level[MAXV];

void gomory_hu(int n) {
    for (int v = 1; v <= n; v++) up[0][v] = 1;
    level[1] = 0;
    for (int s = 2; s <= n; s++) {
        dinic_reset();
        val[0][s] = dinic(s, up[0][s]);
        level[s] = level[up[0][s]] + 1;
        
        memset(cut, 0, sizeof(cut));
        queue<int> q;
        q.push(s);
        cut[s] = 1;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int i: adj[v]) {
                int nxt = edge[i].to;
                if (edge[i].cap && !cut[nxt]) {
                    cut[nxt] = 1;
                    q.push(nxt);
                }
            }
        }
            
        for (int v = s + 1; v <= n; v++)
            if (cut[v] && up[0][v] == up[0][s])
                up[0][v] = s;
    }

    // prepares LCA
    for (int i = 1; i < LOG; i++) {
        for (int v = 1; v <= n; v++) {
            up[i][v] = up[i - 1][up[i - 1][v]];
            val[i][v] = min(val[i - 1][v], val[i - 1][up[i - 1][v]]);
        }
    }
}
