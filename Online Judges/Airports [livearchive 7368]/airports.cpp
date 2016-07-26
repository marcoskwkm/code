#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 510;

typedef int FTYPE;      // define as needed

const int MAXV = 2 * MAXN;
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
    edge.push_back(Edge(u, 0)); // modify to Edge(u, c) if graph is non-directed
    s_edge.push_back(Edge(u, 0));
}

bool dinic_bfs(int _s, int _t) {
    memset(dinic_dist, -1, sizeof(dinic_dist));
    dinic_dist[_s] = 0;
    queue<int> q;
    q.push(_s);
    while(!q.empty() && dinic_dist[_t] == -1) {
        int v = q.front();
        q.pop();
        for(size_t a = 0; a < adj[v].size(); ++a) {
            int ind = adj[v][a];
            int nxt = edge[ind].to;
            if(dinic_dist[nxt] == -1 && edge[ind].cap) {
                dinic_dist[nxt] = dinic_dist[v] + 1;
                q.push(nxt);
            }
        }
    }
    return dinic_dist[_t] != -1;
}

FTYPE dinic_dfs(int v, int _t, FTYPE flow) {
    if(v == _t) return flow;
    for(int &a = ptr[v]; a < (int)adj[v].size(); ++a) {
        int ind = adj[v][a];
        int nxt = edge[ind].to;
        if(dinic_dist[nxt] == dinic_dist[v] + 1 && edge[ind].cap) {
            FTYPE got = dinic_dfs(nxt, _t, min(flow, edge[ind].cap));
            if(got) {
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
    while(dinic_bfs(_s, _t)) {
        memset(ptr, 0, sizeof(ptr));
        while((got = dinic_dfs(_s, _t, FINF))) ret += got;
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
    for(int i = 0; i < MAXV; ++i) adj[i].clear();
    edge.clear();
}

int p[MAXN];
int s[MAXN], f[MAXN], t[MAXN];
int mat[MAXN][MAXN];
int fast[MAXN][MAXN];

int main() {
    int n, m;
    while (scanf("%d%d", &n, &m) > 0) {
        for (int i = 0; i < n; i++) scanf("%d", &p[i]);
        dinic_clear();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", &mat[i][j]);
                fast[i][j] = mat[i][j];
            }
        }
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    fast[i][j] = min(fast[i][j], fast[i][k] + p[k] + fast[k][j]);
        
        for (int i = 0; i < m; i++) {
            scanf("%d%d%d", &s[i], &f[i], &t[i]);
            s[i]--; f[i]--;
        }

        int source = 2*m, sink = 2*m + 1;
        for (int i = 0; i < m; i++) {
            add_edge(source, 2*i, 1);
            add_edge(2*i + 1, sink, 1);
            for (int j = 0; j < m; j++) {
                if (i == j) continue;
                int needs = mat[s[i]][f[i]] + p[f[i]];
                if (f[i] != s[j]) needs += fast[f[i]][s[j]] + p[s[j]];
                if (t[i] + needs <= t[j]) add_edge(2*i, 2*j + 1, 1);
            }
        }

        printf("%d\n", m - dinic(source, sink));
    }        
    return 0;
}
