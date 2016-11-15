#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

typedef int FTYPE;      // define as needed

const int MAXV = 110;
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
inline int add_edge(int u, int v, FTYPE c) {
    int ret = edge.size();
    adj[u].push_back(edge.size());
    edge.push_back(Edge(v, c));
    s_edge.push_back(Edge(v, c));
    adj[v].push_back(edge.size());
    edge.push_back(Edge(u, 0));
    s_edge.push_back(Edge(u, 0));
    return ret;
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

int edge_idx[MAXV];
int n_votes[MAXV];
int voted[MAXV][MAXV];

int main() {
    int n;
    scanf("%d", &n);
    int s = 2*n, t = 2*n + 1;
    for (int i = 0; i < n; i++) {
        add_edge(s, i, 1);
        edge_idx[i] = add_edge(i + n, t, 0);
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(i, u - 1 + n, 1);
        add_edge(i, v - 1 + n, 1);
        n_votes[u - 1]++;
        n_votes[v - 1]++;
        voted[i][u - 1] = voted[i][v - 1] = 1;
    }

    int ans = n;
    for (int i = 0; i < n; i++) {
        if (n_votes[i] <= 1) continue;
        for (int j = 0; j < n; j++) {
            if (i == j) s_edge[edge_idx[j]].cap = n_votes[i];
            else if (voted[i][j]) s_edge[edge_idx[j]].cap = n_votes[i] - 2;
            else s_edge[edge_idx[j]].cap = n_votes[i] - 1;
        }
        dinic_reset();
        if (dinic(s, t) >= n - 1) ans--;
    }

    printf("%d\n", ans);    
    return 0;
}
