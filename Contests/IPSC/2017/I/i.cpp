#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

/* A directed graph */
struct Graph {
    int V;
    vector<vector<int>> adj;
    
    Graph(int _V) : V(_V) {
        adj.resize(V);
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
    }
};

/* Sorts vertices in topological order */
struct TopSort {
    vector<int> ord;
    
    const Graph &g;
    vector<int> indeg;

    TopSort(const Graph &_g) : g(_g) {
        indeg.resize(g.V);
        for (int u = 0; u < g.V; u++)
            for (auto v: g.adj[u])
                indeg[v]++;
        for (int v = 0; v < g.V; v++)
            if (!indeg[v])
                ord.push_back(v);
        for (int i = 0; i < (int)ord.size(); i++) {
            int u = ord[i];
            for (auto v: g.adj[u])
                if (!--indeg[v])
                    ord.push_back(v);
        }
    }
};

/* Finds all SCCs in a directed graph */
struct Tarjan {
    vector<int> cmp_id;      // component of each vertex
    vector<vector<int>> cmp; // list of each component

    const Graph& g;
    vector<int> ind, low;
    vector<bool> in_stack;
    stack<int> st;
    int pre;

    Tarjan(const Graph &_g) : g(_g) {
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

    Graph getContractedGraph() {
        set<pii> seen;
        Graph cg(cmp.size());
        for (int u = 0; u < g.V; u++) {
            for (int v: g.adj[u]) {
                if (cmp_id[u] != cmp_id[v]) {
                    if (seen.find(pii(cmp_id[u], cmp_id[v])) == seen.end()) {
                        seen.insert(pii(cmp_id[u], cmp_id[v]));
                        cg.add_edge(cmp_id[u], cmp_id[v]);
                    }
                }
            }
        }
        return cg;
    }                    
};

const int MAXN = (int)5e5 + 10;
const int P[] = {(int)1e9 + 7, (int)1e9 + 9};
const int NPRIMES = 2;

bool forb[MAXN];
lint n_paths[2][MAXN][NPRIMES];

void get_n_paths(const Graph &g, int s, int i) {
    TopSort ts(g);
    n_paths[i][s][0] = n_paths[i][s][1] = 1;
    for (int v: ts.ord) 
        for (int nxt: g.adj[v])
            for (int p = 0; p < NPRIMES; p++)
                n_paths[i][nxt][p] = (n_paths[i][nxt][p] + n_paths[i][v][p]) % P[p];
}

bool seen[MAXN];
void dfs(Graph &g, int v) {
    seen[v] = 1;
    for (int nxt: g.adj[v])
        if (!seen[nxt])
            dfs(g, nxt);
}

int main() {
    int nt;
    for (scanf("%d", &nt); nt--;) {
        memset(forb, 0, sizeof(forb));
        int n, m;
        scanf("%d%d", &n, &m);
        Graph g(n);
        for (int i = 0; i < m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            if (u == v) forb[u - 1] = 1;
            else g.add_edge(u - 1, v - 1);
        }
        memset(seen, 0, sizeof(seen));
        dfs(g, 0);        
        if (!seen[n - 1]) {
            printf("0\n\n");
            continue;
        }
        
        Tarjan tarjan(g);
        Graph cg = tarjan.getContractedGraph();
        Graph rcg(cg.V);
        for (int v = 0; v < cg.V; v++)
            for (int nxt: cg.adj[v])
                rcg.add_edge(nxt, v);

        int s = tarjan.cmp_id[0], t = tarjan.cmp_id[n - 1];
        memset(n_paths, 0, sizeof(n_paths));
        get_n_paths(cg, s, 0);
        get_n_paths(rcg, t, 1);
        // for (int v = 0; v < n; v++) {
        //     printf("%d: %d %d\n", v + 1, n_paths[0][v][0], n_paths[1][v][0]);
        //     printf("%d: %d %d\n", v + 1, n_paths[0][v][1], n_paths[1][v][1]);
        // }

        vector<int> ans;
        TopSort ts(cg);
        for (int v: ts.ord) {
            if (tarjan.cmp[v].size() > 1 || forb[tarjan.cmp[v][0]]) continue;
            bool ok = 1;
            for (int p = 0; p < NPRIMES; p++) {
                if (n_paths[0][t][p] != (n_paths[0][v][p] * n_paths[1][v][p]) % P[p])
                    ok = 0;
            }
            if (ok) ans.push_back(tarjan.cmp[v][0] + 1);
        }
        printf("%d\n", (int)ans.size());
        for (int x: ans) printf("%d ", x);
        printf("\n");
    }            
    return 0;
}
