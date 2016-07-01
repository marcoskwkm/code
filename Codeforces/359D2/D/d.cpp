#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)3e5 + 10;

int ans[MAXN];
vector<int> adj[MAXN];
int parent[MAXN];
int q[MAXN];
int centroid[MAXN];

void dfs(int v) {
    q[v] = 1;
    int hi = -1, at = -1;
    for (int nxt: adj[v]) {
        dfs(nxt);
        if (q[nxt] > hi) {
            hi = q[nxt];
            at = nxt;
        }
        q[v] += q[nxt];
    }
    if (hi == -1 || 2 * hi <= q[v])
        centroid[v] = v;
    else {
        int cand = centroid[at];
        while (2 * (q[v] - q[cand]) > q[v])
            cand = parent[cand];
        centroid[v] = cand;
    }
}    

int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    for (int v = 2; v <= n; v++) {
        int p;
        scanf("%d", &p);
        parent[v] = p;
        adj[p].push_back(v);
    }
    dfs(1);
    while (q--) {
        int v;
        scanf("%d", &v);
        printf("%d\n", centroid[v]);
    }    
    return 0;
}
