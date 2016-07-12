#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 32;

typedef int FTYPE;      // define as needed

const int MAXV = 2000;
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

int dr[] = {1, 0, -1, 0};
int dc[] = {0, 1, 0, -1};

int main() {
    while (1) {
        vector<string> grid;
        string line;
        if (!getline(cin, line)) break;
        grid.push_back(line);
        while (1) {
            getline(cin, line);
            if (line.size() == 0) break;
            grid.push_back(line);
        }
        int n = grid.size();
        int m = grid[0].size();
        dinic_clear();
        int s = 2*n*m, t = 2*n*m + 1;
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                for (int i = 0; i < 4; i++) {
                    int nr = r + dr[i], nc = c + dc[i];
                    if (nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
                    if ( (grid[r][c] == 'W' && grid[nr][nc] == 'I') ||
                         (grid[r][c] == 'I' && grid[nr][nc] == 'N') ) {
                        int u = 2*(m*r + c), v = 2*(m*nr + nc);
                        if (grid[r][c] == 'I') u += 1;
                        add_edge(u, v, 1);
                    }
                }
                if (grid[r][c] == 'W') add_edge(s, 2*(m*r + c), 1);
                if (grid[r][c] == 'I') add_edge(2*(m*r + c), 2*(m*r + c) + 1, 1);
                if (grid[r][c] == 'N') add_edge(2*(m*r + c), t, 1);
            }
        }
        printf("%d\n", dinic(s, t));
    }        
    return 0;
}
