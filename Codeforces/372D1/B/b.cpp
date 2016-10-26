#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;
typedef tuple<int, int, lint> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 1000000000000000000ll;
const int MAXN = 1010, MAXM = (int)1e4 + 10;

vector<tiii> adj[MAXN];
lint dist[MAXN];
bool erased[MAXM];
int n, m, L, s, t;

void dijkstra(int s, int k, lint c) {
    for (int v = 0; v < n; v++) dist[v] = LINF;
    dist[s] = 0;
    set<pll> pq;
    pq.insert(pll(0, s));
    while (!pq.empty()) {
        int v = pq.begin()->second;
        pq.erase(pq.begin());
        for (tiii edge: adj[v]) {
            int nxt, cst, i;
            tie(nxt, cst, i) = edge;            
            lint newd = min(dist[v] + cst, LINF);
            if (erased[i]) {
                if (i < k) newd = min(dist[v] + c + 1, LINF);
                else newd = min(dist[v] + c, LINF);
            }                
            if (dist[nxt] > newd) {
                pq.erase(pll(dist[nxt],nxt));
                dist[nxt] = newd;
                pq.insert(pll(dist[nxt], nxt));
            }
        }
    }
}

bool seen[MAXN];
void dfs(int v) {
    seen[v] = 1;
    for (tiii edge: adj[v]) {
        int nxt = get<0>(edge);
        if (!seen[nxt])
            dfs(nxt);
    }
}

int main() {
    scanf("%d%d%d%d%d", &n, &m, &L, &s, &t);
    vector<tiii> edges;
    for (int i = 0; i < m; i++) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        adj[u].push_back(tiii(v, c, i));
        adj[v].push_back(tiii(u, c, i));
        edges.push_back(tiii(u, v, c));
        if (c == 0) erased[i] = 1;
    }

    dfs(s);
    if (!seen[t]) {
        printf("NO\n");
        return 0;
    }
    
    dijkstra(s, 0, LINF);
    if (dist[t] < L) {
        printf("NO\n");
        return 0;
    }

    dijkstra(s, 0, 1);
    if (dist[t] > L) {
        printf("NO\n");
        return 0;
    }

    lint l = 1, r = LINF - 1;
    while (l < r) {
        lint mid = (l + r) / 2;
        dijkstra(s, m, mid);
        if (dist[t] < L) l = mid + 1;
        else r = mid;
    }

    lint cst = l;
    l = 0, r = m;
    while (l < r) {
        lint mid = (l + r) / 2;
        dijkstra(s, mid, cst);
        if (dist[t] < L) l = mid + 1;
        else r = mid;
    }

    dijkstra(s, l, cst);
    // assert(dist[t] == L);
    // printf("dist[%d] = %lld\n", t, dist[t]);
    printf("YES\n");
    for (int i = 0; i < m; i++) {
        int u, v, c;
        tie(u, v, c) = edges[i];
        printf("%d %d ", u, v);
        if (c != 0) printf("%d\n", c);
        else cout << (i < l ? cst + 1 : cst) << endl;
    }        
    return 0;
}
