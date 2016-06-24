#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

typedef int FTYPE;      // define as needed

const int MAXV = 6010;
const FTYPE FINF = INF; // infinite flow

struct Edge {
    int to;    
    FTYPE cap;
    Edge(int t = 0, FTYPE c = 0) { to = t; cap = c; }
};

vector<int> adj[MAXV];
Edge edge[3000*3000*2 + 10];
int n_edges;
int ptr[MAXV], dinic_dist[MAXV];

// Inserts an edge u->v with capacity c
inline void add_edge(int u, int v, FTYPE c) {
    adj[u].push_back(n_edges);
    edge[n_edges++] = Edge(v, c);
    adj[v].push_back(n_edges);
    edge[n_edges++] = Edge(u, 0);
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

lint x[MAXV], y[MAXV];
lint l[MAXV], r[MAXV];
int greedy[MAXV];

int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    for (int i = 0; i < q; i++)
        cin >> x[i] >> y[i] >> l[i] >> r[i];
    for (int i = 0; i < q; i++) {
        for (int j = 0; j < q; j++) {
            if (i == j) continue;
            if (l[j] < r[i]) continue;
            lint d = (x[j] - x[i])*(x[j] - x[i]) + (y[j] - y[i])*(y[j] - y[i]);
            lint t = (r[i] - l[j])*(r[i] - l[j]);
            if (r[i] <= l[j] && d <= t) add_edge(2*i, 2*j + 1, 1);
        }
    }
    memset(greedy, -1, sizeof(greedy));
    // greedy matching
    int start = 0;
    for (int i = 0; i < q; i++) {
        for (int idx: adj[2*i]) {
            int nxt = edge[idx].to;
            if (greedy[nxt] != -1) continue;
            greedy[2*i] = nxt;
            greedy[nxt] = 2*i;
            edge[idx].cap -= 1;
            edge[idx^1].cap += 1;
            start++;
            break;
        }
    }
    
    int s = 2*q, t = 2*q + 1;
    for (int i = 0; i < q; i++) {
        if (greedy[2*i] == -1) add_edge(s, 2*i, 1);
        if (greedy[2*i + 1] == -1) add_edge(2*i + 1, t, 1);
    }
    int flow = dinic(s, t);
    int needs = q - flow - start;
    printf("%c\n", n >= needs ? 'S' : 'N');    
    return 0;
}
