#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

typedef int FTYPE;      // define as needed
typedef tuple<char, int, int> Modification;

const int MAXN = 110;
const int MAXV = 10 * MAXN;
const int OFF = 2 * MAXN;
const FTYPE FINF = INF; // infinite flow

struct Edge {
    int to;    
    FTYPE cap;
    Edge(int t, FTYPE c) { to = t; cap = c; }
};

vector<int> adj[MAXV];
vector<Edge> edge, s_edge;
int ptr[MAXV], dinic_dist[MAXV];

// Inserts an edge u->v with capacity c
inline void add_edge(int u, int v, FTYPE c) {
    adj[u].push_back(edge.size());
    edge.push_back(Edge(v, c));
    s_edge.push_back(Edge(v, c));
    adj[v].push_back(edge.size());
    edge.push_back(Edge(u, 0));
    s_edge.push_back(Edge(u, 0));
}

bool dinic_bfs(int _s, int _t) {
    memset(dinic_dist, -1, sizeof(dinic_dist));
    dinic_dist[_s] = 0;
    queue<int> q;
    q.push(_s);
    while (!q.empty() && dinic_dist[_t] == -1) {
        int v = q.front();
        q.pop();
        for (size_t a = 0; a < adj[v].size(); ++a) {
            int ind = adj[v][a];
            int nxt = edge[ind].to;
            if (dinic_dist[nxt] == -1 && edge[ind].cap) {
                dinic_dist[nxt] = dinic_dist[v] + 1;
                q.push(nxt);
            }
        }
    }
    return dinic_dist[_t] != -1;
}

FTYPE dinic_dfs(int v, int _t, FTYPE flow) {
    if (v == _t) return flow;
    for (int &a = ptr[v]; a < (int)adj[v].size(); ++a) {
        int ind = adj[v][a];
        int nxt = edge[ind].to;
        if (dinic_dist[nxt] == dinic_dist[v] + 1 && edge[ind].cap) {
            FTYPE got = dinic_dfs(nxt, _t, min(flow, edge[ind].cap));
            if (got) {
                edge[ind].cap -= got;
                edge[ind^1].cap += got;
                return got;
            }
        }
    }
    return 0;
}

FTYPE dinic(int _s, int _t) {
    FTYPE ret = 0, got;
    while (dinic_bfs(_s, _t)) {
        memset(ptr, 0, sizeof(ptr));
        while ((got = dinic_dfs(_s, _t, FINF))) ret += got;
    }
    return ret;
}

// Removes all flow but keeps graph structure
void dinic_reset() {
    for (int i = 0; i < (int)edge.size(); i++)
        edge[i].cap = s_edge[i].cap;
}

// Clears dinic structure
inline void dinic_clear() {
    for (int i = 0; i < MAXV; ++i) adj[i].clear();
    edge.clear();
}

char grid[MAXN][MAXN];
char sol[MAXN][MAXN];
int rev[MAXV];

int main() {
    int t = 1, T;
    for (scanf("%d", &T); t <= T; t++) {
        printf("Case #%d: ", t);
        int n, m;
        scanf("%d%d", &n, &m);
        memset(grid, '.', sizeof(grid));
        int points = 0;
        set<int> blocked_rows, blocked_cols, blocked_diag1, blocked_diag2;
        for (int i = 0; i < m; i++) {
            char k;
            int r, c;
            scanf(" %c%d%d", &k, &r, &c);
            grid[r][c] = k;
            if (k == '+' || k == 'x') points += 1;
            else if (k == 'o') points += 2;
            if (k == '+' || k == 'o') {
                blocked_diag1.insert(r - c);
                blocked_diag2.insert(r + c);
            }
            if (k == 'x' || k == 'o') {
                blocked_rows.insert(r);
                blocked_cols.insert(c);
            }
        }
        memcpy(sol, grid, sizeof(grid));
        
        dinic_clear();
        map<int, int> row_idx, col_idx, diag1_idx, diag2_idx;
        int cnt = 0;
        int s1 = cnt++;
        int t1 = cnt++;
        int s2 = cnt++;
        int t2 = cnt++;
        for (int i = 1; i <= n; i++) {
            rev[cnt] = i;
            row_idx[i] = cnt++;
            rev[cnt] = i;
            col_idx[i] = cnt++;
            if (blocked_rows.find(i) == blocked_rows.end())
                add_edge(s1, row_idx[i], 1);
            if (blocked_cols.find(i) == blocked_cols.end())
                add_edge(col_idx[i], t1, 1);
        }
        for (int i = 1 - n; i <= n - 1; i++) {
            rev[cnt] = i;
            diag1_idx[i] = cnt++;
            if (blocked_diag1.find(i) == blocked_diag1.end())
                add_edge(s2, diag1_idx[i], 1);
        }
        for (int i = 1 + 1; i <= n + n; i++) {
            rev[cnt] = i;
            diag2_idx[i] = cnt++;
            if (blocked_diag2.find(i) == blocked_diag2.end())
                add_edge(diag2_idx[i], t2, 1);
        }        
        for (int r = 1; r <= n; r++) {
            for (int c = 1; c <= n; c++) {
                add_edge(row_idx[r], col_idx[c], 1);
                add_edge(diag1_idx[r - c], diag2_idx[r + c], 1);
            }
        }

        points += dinic(s1, t1);
        points += dinic(s2, t2);

        for (int r = 1; r <= n; r++) {
            int idx = row_idx[r];
            for (int i: adj[idx]) {
                if (edge[i].cap == 0 && edge[i].to != s1) {
                    int c = rev[edge[i].to];
                    if (sol[r][c] == '.')
                        sol[r][c] = 'x';
                    else if (sol[r][c] == '+')
                        sol[r][c] = 'o';
                    else abort();
                }
            }
        }
        for (int d1 = 1 - n; d1 <= n - 1; d1++) {
            int idx = diag1_idx[d1];
            for (int i: adj[idx]) {
                if (edge[i].cap == 0 && edge[i].to != s2) {
                    int d2 = rev[edge[i].to];
                    int r = (d1 + d2) / 2;
                    int c = (d2 - d1) / 2;
                    if (sol[r][c] == '.')
                        sol[r][c] = '+';
                    else if (sol[r][c] == 'x')
                        sol[r][c] = 'o';
                    else abort();
                }
            }
        }

        vector<Modification> ans;
        for (int r = 1; r <= n; r++)
            for (int c = 1; c <= n; c++)
                if (sol[r][c] != grid[r][c])
                    ans.push_back(Modification(sol[r][c], r, c));
        printf("%d %d\n", points, (int) ans.size());
        for (auto mod: ans)
            printf("%c %d %d\n", get<0>(mod), get<1>(mod), get<2>(mod));
    }        
    return 0;
}
