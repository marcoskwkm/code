// Dinic maxflow, min(O(EV^2),O(maxflow*E)(?)) worst case
// O(E*min(V^2/3,sqrt(E))) for unit caps (O(E*sqrt(V)) if bipartite)

typedef int FTYPE;      // define as needed

const int MAXV = 5010;
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
