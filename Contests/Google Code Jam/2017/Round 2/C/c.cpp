#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;
typedef tuple<int, int, int, int> tiiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 55;
const int MAXR = 110;

/* A directed graph */
struct Graph {
    int V, E;
    vector<vector<int>> adj;
    
    Graph(int _V) : V(_V) {
        adj.resize(V);
    }

    set<pii> seen;
    void add_edge(int u, int v) {
        if (seen.find(pii(u, v)) != seen.end()) return;
        seen.insert(pii(u, v));
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

int R, C;
char grid[MAXN][MAXN];
int ray_id[MAXN][MAXN];
int cmp_id[MAXN][MAXN][2]; // 0 - hor, 1 - ver
int dr[] = {0, -1, 0, 1};
int dc[] = {1, 0, -1, 0};
vector<pii> rays[2 * MAXN * MAXN];

int cur_test;

void dfs(int _r, int _c, int _d, int _id) {
    stack<tiiii> st;
    st.push(tiiii(_r, _c, _d, _id));
    while (!st.empty()) {
        int r, c, d, id;
        tie(r, c, d, id) = st.top();
        st.pop();
        if (r < 0 || c < 0 || r >= R || c >= C || grid[r][c] == '#')
            continue;
        if (grid[r][c] == '|' || grid[r][c] == '-')
            rays[id].push_back(pii(ray_id[r][c], d % 2));
        if (cmp_id[r][c][d % 2] != -1)
            continue;
        if (grid[r][c] == '/') {
            if (d == 0) st.push(tiiii(r - 1, c, 1, id));
            else if (d == 1) st.push(tiiii(r, c + 1, 0, id));
            else if (d == 2) st.push(tiiii(r + 1, c, 3, id));
            else if (d == 3) st.push(tiiii(r, c - 1, 2, id));
            continue;
        }
        else if (grid[r][c] == '\\') {
            if (d == 0) st.push(tiiii(r + 1, c, 3, id));
            else if (d == 1) st.push(tiiii(r, c - 1, 2, id));
            else if (d == 2) st.push(tiiii(r - 1, c, 1, id));
            else if (d == 3) st.push(tiiii(r, c + 1, 0, id));
            continue;
        }
        cmp_id[r][c][d % 2] = id;
        int nr = r + dr[d], nc = c + dc[d];
        st.push(tiiii(nr, nc, d, id));
    }
}

int main() {
    int t = 1, T;
    for (scanf("%d", &T); t <= T; t++) {
        cur_test = t;
        debug("Test %d...\n", t);
        printf("Case #%d: ", t);
        for (int i = 0; i < 2 * MAXN * MAXN; i++)
            rays[i].clear();
        scanf("%d%d", &R, &C);
        int n_rays = 0;
        for (int r = 0; r < R; r++) {
            for (int c = 0; c < C; c++) {
                scanf(" %c", &grid[r][c]);
                if (grid[r][c] == '|' || grid[r][c] == '-')
                    ray_id[r][c] = n_rays++;
            }
        }
        grid[0][C] = 0;
        memset(cmp_id, -1, sizeof(cmp_id));
        Graph g(2 * n_rays);
        int n_cmp = 0;
        bool ok = 1;
        for (int r = 0; r < R; r++) {
            for (int c = 0; c < C; c++) {
                if (grid[r][c] != '.' && grid[r][c] != '-' && grid[r][c] != '|') continue;
                if (cmp_id[r][c][0] == -1) {
                    dfs(r, c - 1, 2, n_cmp);
                    dfs(r, c, 0, n_cmp++);
                    if (rays[cmp_id[r][c][0]].size() > 1) {
                        for (pii p: rays[cmp_id[r][c][0]])
                            g.add_edge(2*p.first + p.second, 2*p.first + (1 - p.second));
                    }                    
                }
                if (cmp_id[r][c][1] == -1) {
                    dfs(r - 1, c, 1, n_cmp);
                    dfs(r, c, 3, n_cmp++);
                    if (rays[cmp_id[r][c][1]].size() > 1) {
                        for (pii p: rays[cmp_id[r][c][1]])
                            g.add_edge(2*p.first + p.second, 2*p.first + (1 - p.second));
                    }
                }
                int ch = cmp_id[r][c][0], cv = cmp_id[r][c][1];
                // debug("(%d, %d): %d(%d), %d(%d)\n", r, c, ch, rays[ch].size(), cv, rays[cv].size());
                if (grid[r][c] != '.') {
                    if (ch == cv) ok = 0;
                }
                else {
                    if (rays[ch].size() == 1 && rays[cv].size() == 1) {
                        pii rh = rays[ch][0], rv = rays[cv][0];
                        g.add_edge(2*rh.first + (1 - rh.second), 2*rv.first + rv.second);
                        g.add_edge(2*rv.first + (1 - rv.second), 2*rh.first + rh.second);
                    }
                    else if (rays[ch].size() == 1) {
                        pii rh = rays[ch][0];
                        g.add_edge(2*rh.first + (1 - rh.second), 2*rh.first + rh.second);
                    }
                    else if (rays[cv].size() == 1) {
                        pii rv = rays[cv][0];
                        g.add_edge(2*rv.first + (1 - rv.second), 2*rv.first + rv.second);
                    }
                    else ok = 0;
                }
            }
        }
        SatSolver sat(g);
        if (!ok || !sat.solvable) {
            printf("IMPOSSIBLE\n");
            continue;
        }
        printf("POSSIBLE\n");
        for (int r = 0; r < R; r++) {
            for (int c = 0; c < C; c++) {
                if (grid[r][c] != '-' && grid[r][c] != '|')
                    printf("%c", grid[r][c]);
                else {
                    if (sat.value[2*ray_id[r][c]] == 1)
                        printf("-");
                    else printf("|");
                }
            }
            printf("\n");
        }
    }
    return 0;
}
