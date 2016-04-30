#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

typedef int FTYPE;      // define as needed

const int MAXV = 210;
const FTYPE FINF = INF; // infinite flow
const int MAXN = 110;

struct Edge {
    int to;    
    FTYPE cap;
    Edge(int t, FTYPE c) { to = t; cap = c; }
};

vector<int> adj[MAXV];
vector<Edge> edge;
int ptr[MAXV], dinic_dist[MAXV];

// Inserts an edge u->v with capacity c
inline void add_edge(int u,int v,FTYPE c) {
    adj[u].push_back(edge.size());
    edge.push_back(Edge(v,c));
    adj[v].push_back(edge.size());
    edge.push_back(Edge(u,0)); // modify to Edge(u,c) if graph is non-directed
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

// Clears dinic structure
inline void dinic_clear() {
    for(int a=0;a<MAXV;++a) adj[a].clear();
    edge.clear();
}

int v[MAXN];
int good[MAXN][2];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    set<int> primes;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &v[i]);
        int tmp = v[i];
        for (int d = 2; d*d <= tmp; d++) {
            while (tmp % d == 0) {
                tmp /= d;
                primes.insert(d);
            }
        }
        if (tmp > 1) primes.insert(tmp);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &good[i][0], &good[i][1]);
        if (good[i][1] & 1) swap(good[i][0], good[i][1]);
    }

    int ans = 0;
    for (int p: primes) {
        dinic_clear();
        int s = 0, t = n + 1;
        for (int i = 1; i <= n; i++) {
            int tmp = v[i];
            int cap = 0;
            while (tmp % p == 0) {
                tmp /= p;
                cap++;
            }
            if (cap) {
                if (i & 1) add_edge(s, i, cap);
                else add_edge(i, t, cap);
            }
        }
        for (int i = 0; i < m; i++)
            add_edge(good[i][0], good[i][1], INF);
        ans += dinic(s, t);
    }
    printf("%d\n", ans);        
    return 0;
}
