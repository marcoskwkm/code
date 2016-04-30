#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

// Dinic maxflow, min(O(EV^2),O(maxflow*E)(?)) worst case
// O(E*min(V^2/3,sqrt(E))) for unit caps (O(E*sqrt(V)) if bipartite)

typedef int FTYPE;      // define as needed

const int MAXV = 3010;
const FTYPE FINF = INF; // infinite flow

struct Edge {
    int to;    
    FTYPE cap;
    Edge(int t, FTYPE c) { to = t; cap = c; }
};

vector<int> adj[MAXV];
vector<Edge> edge;
vector<Edge> sedge;
int ptr[MAXV], dinic_dist[MAXV];

// Inserts an edge u->v with capacity c
inline void add_edge(int u,int v,FTYPE c) {
    adj[u].push_back(edge.size());
    edge.push_back(Edge(v, c));
    sedge.push_back(Edge(v, c));
    adj[v].push_back(edge.size());
    edge.push_back(Edge(u, c));
    sedge.push_back(Edge(u, c));
}

bool dinic_bfs(int _s,int _t) {
    memset(dinic_dist,-1,sizeof(dinic_dist));
    dinic_dist[_s] = 0;
    queue<int> q;
    q.push(_s);
    while(!q.empty() && dinic_dist[_t] == -1) {
        int v = q.front();
        q.pop();
        for(size_t a=0;a<adj[v].size();++a) {
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

FTYPE dinic_dfs(int v,int _t,FTYPE flow) {
    if(v == _t) return flow;
    for(int &a = ptr[v];a<(int)adj[v].size();++a) {
        int ind = adj[v][a];
        int nxt = edge[ind].to;
        if(dinic_dist[nxt] == dinic_dist[v] + 1 && edge[ind].cap) {
            FTYPE got = dinic_dfs(nxt,_t,min(flow,edge[ind].cap));
            if(got) {
                edge[ind].cap -= got;
                edge[ind^1].cap += got;
                return got;
            }
        }
    }
    return 0;
}

FTYPE dinic(int _s,int _t) {
    FTYPE ret = 0, got;
    while(dinic_bfs(_s,_t)) {
        memset(ptr,0,sizeof(ptr));
        while((got = dinic_dfs(_s,_t,FINF))) ret += got;
    }
    return ret;
}

void dinic_reset() {
    for (int i = 0; i < (int)edge.size(); i++)
        edge[i].cap = sedge[i].cap;
}

// Clears dinic structure
inline void dinic_clear() {
    for(int a=0;a<MAXV;++a) adj[a].clear();
    edge.clear();
}

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

int lca(int u, int v) {
    int ret = INF;
    if (level[u] < level[v]) swap(u, v);
    if (level[u] > level[v]) {
        for (int i = LOG - 1; i >= 0; i--) {
            if (level[up[i][u]] > level[v]) {
                ret = min(ret, val[i][u]);
                u = up[i][u];
            }
        }
        ret = min(ret, val[0][u]);
        u = up[0][u];
    }
    if (u == v) {
        return ret;
    }
    for (int i = LOG - 1; i >= 0; i--) {
        if (up[i][u] != up[i][v]) {
            ret = min(ret, min(val[i][u], val[i][v]));
            u = up[i][u];
            v = up[i][v];
        }
    }
    return min(ret, min(val[0][u], val[0][v]));
}        

int main() {
    int n, m;
    while (scanf("%d%d", &n, &m) > 0) {
        dinic_clear();
        for (int i = 0; i < m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            add_edge(u, v, 1);
        }

        gomory_hu(n);

        int ans = 0;
        for (int u = 1; u <= n; u++) {
            for (int v = u + 1; v <= n; v++) {
                ans += lca(u, v);
            }
        }
        printf("%d\n", ans);
    }        
    return 0;
}
