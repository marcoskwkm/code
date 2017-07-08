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

/* Finds one solution for a 2-sat instance or informs there isn't one */
struct SatSolver {
    bool solvable;
    vector<int> value; // 0 - false, 1 - true
    
    const Graph &g;

    SatSolver(const Graph &_g) : g(_g) {
        value.resize(g.V);
        Tarjan tarjan(g);
        for (int v = 0; v < g.V; v += 2) {
            if (tarjan.cmp_id[v] == tarjan.cmp_id[v + 1]) {
                solvable = false;
                return;
            }
        }
        solvable = true;
        Graph gc = tarjan.getContractedGraph();
        TopSort ts(gc);
        vector<int> _value(gc.V, -1);
        for (int c: ts.ord) {
            if (_value[c] == -1) {
                _value[c] = 0;
                for (int v: tarjan.cmp[c]) {
                    value[v] = 0;
                    value[v ^ 1] = 1;
                    _value[tarjan.cmp_id[v ^ 1]] = 1;
                }
            }
        }
    }
};

const int MAXN = 1010;

vector<pii> rows[MAXN], cols[MAXN];

int main() {
    int n, k, l;
    scanf("%d%d%d", &n, &k, &l);
    vector<pii> lamp;
    for (int i = 0; i < l; i++) {
        int r, c;
        scanf("%d%d", &r, &c);
        lamp.push_back(pii(r, c));
        rows[r].push_back(pii(c, i));
        cols[c].push_back(pii(r, i));
    }
    Graph g(2*l);
    for (int r = 1; r <= n; r++) {
        sort(rows[r].begin(), rows[r].end());
        for (int i = 0; i < (int)rows[r].size(); i++) {
            int u = 2*rows[r][i].second;
            for (int j = i + 1; j < (int)rows[r].size(); j++) {
                int v = 2*rows[r][j].second;
                if (rows[r][j].first - rows[r][i].first - 1 < 2*k) {
                    g.add_edge(u, v^1);
                    g.add_edge(v, u^1);
                }
            }
        }
    }
    for (int c = 1; c <= n; c++) {
        sort(cols[c].begin(), cols[c].end());
        for (int i = 0; i < (int)cols[c].size(); i++) {
            int u = 2*cols[c][i].second + 1;
            for (int j = i + 1; j < (int)cols[c].size(); j++) {
                int v = 2*cols[c][j].second + 1;
                if (cols[c][j].first - cols[c][i].first - 1 < 2*k) {
                    g.add_edge(u, v^1);
                    g.add_edge(v, u^1);
                }
            }
        }
    }

    SatSolver sat(g);
    printf("%s\n", sat.solvable ? "YES" : "NO");    
    return 0;
}
