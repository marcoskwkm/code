#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;

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

int q[MAXN];
int dfs(int v, Graph &g, Tarjan &t) {
    if (q[v] > 0) return q[v];
    q[v] = t.cmp[v].size();
    int add = 0;
    for (int nxt: g.adj[v]) {
        add = max(add, dfs(nxt, g, t));
    }
    q[v] += add;
    return q[v];
}

int indeg[MAXN];

int main() {
    int n, m;
    cin >> n >> m;
    Graph g(n);
    while (m--) {
        int u, v;
        scanf("%d%d", &u, &v);
        g.add_edge(u - 1, v - 1);
    }

    Tarjan tarjan(g);
    Graph gg = tarjan.getContractedGraph();
    // for (int i = 0; i < n; i++)
    //     printf("%d: %d\n", i, tarjan.cmp_id[i]);
    // printf("--\n");
    // for (int i = 0; i < gg.V; i++) {
    //     printf("%d:", i);
    //     for (int x: tarjan.cmp[i])
    //         printf(" %d", x);
    //     printf("\n");
    // }

    for (int v = 0; v < gg.V; v++)
        for (int nxt: gg.adj[v])
            indeg[nxt]++;
        
    int high = 0, ans = 0;
    for (int v = 0; v < gg.V; v++) {
        int got = dfs(v, gg, tarjan);
//        printf("cmp %d: %d\n", v, got);
        if (got > high) {
            high = got;
            ans = tarjan.cmp[v].size();
        }
        else if (got == high)
            ans += tarjan.cmp[v].size();
    }

    printf("%d %d\n", high, ans);    
    return 0;
}
