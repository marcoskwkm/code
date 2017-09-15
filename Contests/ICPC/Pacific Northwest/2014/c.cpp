#include <bits/stdc++.h>
using namespace std;

typedef long long lint;
typedef pair<int ,int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;

typedef int FTYPE;      // define as needed

const int MAXV = 2010;
const FTYPE FINF = INF; // infinite flow

struct Edge {
    int to;    
    FTYPE cap;
    Edge(int t, FTYPE c) { to = t; cap = c; }
};

vector<int> adj[MAXV];
vector<Edge> edge, s_edge;
int ptr[MAXV], dinic_dist[MAXV];

inline void add_edge(int u, int v, FTYPE c) {
    adj[u].push_back(edge.size());
    edge.push_back(Edge(v, c));
    s_edge.push_back(Edge(v, c));
    adj[v].push_back(edge.size());
    edge.push_back(Edge(u, c));
    s_edge.push_back(Edge(u, c));
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

// Clears dinic structure
inline void dinic_clear() {
    for (int i = 0; i < MAXV; ++i) adj[i].clear();
    edge.clear();
}

int get_id(int x, int y, int z) {
    return 100*x + 10*y + z;
}

int main() {
    int T;
    for (scanf("%d", &T); T--;) {
        dinic_clear();
        int s = 1000, t = 1001;
        for (int x = 0; x < 10; x++) {
            for (int y = 0; y < 10; y++) {
                for (int z = 0; z < 10; z++) {
                    int id = get_id(x, y, z);
                    if (x < 9) add_edge(id, get_id(x + 1, y, z), 1);
                    if (y < 9) add_edge(id, get_id(x, y + 1, z), 1);
                    if (z < 9) add_edge(id, get_id(x, y, z + 1), 1);
                    if (x == 0 || x == 9) add_edge(s, id, 1);
                    if (y == 0 || y == 9) add_edge(s, id, 1);
                    if (z == 0 || z == 9) add_edge(s, id, 1);
                }
            }
        }

        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            add_edge(get_id(x, y, z), t, INF);
        }

        printf("%d\n", dinic(s, t));
    }        
    return 0;
}
   
