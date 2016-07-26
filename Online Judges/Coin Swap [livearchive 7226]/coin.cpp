#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;


typedef int FTYPE; // type of flow
typedef int CTYPE; // type of cost
typedef pair<FTYPE,CTYPE> pfc; // pair<flow,cost>

const int MAXV = 510;
const CTYPE CINF = INF; // infinite cost
const FTYPE FINF = INF; // infinite flow

void operator+=(pfc &p1,pfc &p2) { p1.first += p2.first; p1.second += p2.second; }

struct Edge {
    int to;
    FTYPE cap;
    CTYPE cost;
    Edge(int a,FTYPE cp,CTYPE ct) { to = a; cap = cp; cost = ct; }
};

vector<int> adj[MAXV];
vector<Edge> edge;
int V = 510; // number of vertices (don't forget to set!)

// Inserts an edge u->v with capacity c and cost cst
inline void add_edge(int u,int v,FTYPE c,CTYPE cst) {
    adj[u].push_back(edge.size());
    edge.push_back(Edge(v,c,cst));
    adj[v].push_back(edge.size());
    edge.push_back(Edge(u,0,-cst));
}

FTYPE flow[MAXV];
CTYPE dist[MAXV], pot[MAXV];
int prv[MAXV], e_ind[MAXV];
bool foi[MAXV];

void bellman_ford(int _s) {
    for(int a=0;a<V;++a) dist[a] = CINF;
    dist[_s] = 0;
    for(int st=0;st<V;++st) {
        for(int v=0;v<V;++v) {
            for(size_t a=0;a<adj[v].size();++a) {
                int ind = adj[v][a];
                int nxt = edge[ind].to;
                if(!edge[ind].cap) continue;
                dist[nxt] = min(dist[nxt],dist[v] + edge[ind].cost);
            }
        }
    }
}

pfc dijkstra(int _s,int _t) { // O(V^2)
    for(int a=0;a<V;++a) {
        dist[a] = CINF;
        foi[a] = 0;
    }
    dist[_s] = 0;
    flow[_s] = FINF;
    while(1) {
        int v;
        CTYPE d = CINF;
        for(int a=0;a<V;++a) {
            if(foi[a] || dist[a] >= d) continue;
            d = dist[a];
            v = a;
        }
        if(d == CINF) break;
        foi[v] = 1;
        for(size_t a=0;a<adj[v].size();++a) {
            int ind = adj[v][a];
            int nxt = edge[ind].to;
            if(!edge[ind].cap || dist[nxt] <= dist[v] + edge[ind].cost + pot[v] - pot[nxt]) continue;
            dist[nxt] = dist[v] + edge[ind].cost + pot[v] - pot[nxt];
            prv[nxt] = v;
            e_ind[nxt] = ind;
            flow[nxt] = min(flow[v],edge[ind].cap);
        }
    }
    if(dist[_t] == CINF) return pfc(FINF,CINF);
    for(int a=0;a<V;++a) pot[a] += dist[a];
    pfc ret(flow[_t],0);
    for(int cur = _t; cur != _s; cur = prv[cur]) {
        int ind = e_ind[cur];
        edge[ind].cap -= flow[_t];
        edge[ind^1].cap += flow[_t];
        ret.second += flow[_t] * edge[ind].cost; // careful with overflow!
    }
    return ret;
}

// Returns a pair (max-flow, min-cost)
pfc mcmf(int _s,int _t) {
    pfc ret(0,0), got;
    bellman_ford(_s);
    for(int a=0;a<V;++a) pot[a] = dist[a];
    while( (got = dijkstra(_s,_t)).first != FINF ) ret += got;
    return ret;
}

// Clears mcmf structure
inline void mcmf_clear() {
    edge.clear();
    for(int a=0;a<V;++a) adj[a].clear();
}

int qv[MAXV], qc[MAXV];
int cv[MAXV], cc[MAXV];

int main() {
    int tt;
    for (scanf("%d", &tt); tt--;) {
        int n, m;
        scanf("%d%d", &n, &m);
        mcmf_clear();
        for (int i = 0; i < m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            add_edge(u, v, FINF, 1);
            add_edge(v, u, FINF, 1);
        }
        int s = n + 1, t = n + 2;
        for (int v = 1; v <= n; v++) {
            scanf("%d", &cv[v]);
            if (cv[v] == 1) add_edge(v, t, 1, 0);
        }
        for (int v = 1; v <= n; v++) {
            scanf("%d", &cc[v]);
            if (cc[v] == 1) add_edge(s, v, 1, 0);
        }
        printf("%d\n", mcmf(s, t).second);
    }        
    return 0;
}
