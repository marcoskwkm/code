#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)4e5 + 10;

vector<int> adj[MAXN];
set<pii> forb;

namespace bap {
    int ind[MAXN], low[MAXN];
    int cnt;
    
    void dfs(int v, int prev = -1) {
        ind[v] = low[v] = cnt++;
        int cont = 0;
        for (int nxt: adj[v]) {
            if (ind[nxt] == -1) {
                ++cont;
                dfs(nxt, v);
                low[v] = min(low[v], low[nxt]);
                if (low[nxt] == ind[nxt]) {
                    forb.insert(pii(v, nxt));
                    forb.insert(pii(nxt, v));
                    // v-nxt is a bridge
                }
            }
            else if (nxt != prev) low[v] = min(low[v], ind[nxt]);
        }
    }

    void init() {
        memset(ind, -1, sizeof(ind));
        cnt = 0;
    }
}

int cmp[MAXN], cmp_size[MAXN];
set<pii> ans;
int ind[MAXN], cnt;

void dfs(int v, int prv, int c) {
    cmp_size[cmp[v] = c]++;
    ind[v] = cnt++;
    for (int nxt: adj[v]) {
        if (nxt == prv) continue;
        if (forb.find(pii(v, nxt)) != forb.end()) continue;
        if (cmp[nxt] == -1) {
            dfs(nxt, v, c);
            ans.insert(pii(v, nxt));
        }
        else if (ind[nxt] < ind[v])
            ans.insert(pii(v, nxt));
    }
}

bool seen[MAXN];
void dfs2(int v, int prv) {
    seen[v] = 1;
    for (int nxt: adj[v]) {
        if (nxt == prv || seen[nxt]) continue;
        if (cmp[v] != cmp[nxt]) ans.insert(pii(nxt, v));
        dfs2(nxt, v);
    }
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<pii> edges;
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
        edges.push_back(pii(u, v));
    }
    bap::init();
    for (int v = 1; v <= n; v++)
        if (bap::ind[v] == -1)
            bap::dfs(v);

    memset(cmp, -1, sizeof(cmp));
    int ncmp = 0;
    cnt = 0;
    int hi = 0, at = -1;
    for (int v = 1; v <= n; v++) {
        if (cmp[v] == -1) {
            dfs(v, -1, ncmp++);
            if (cmp_size[ncmp - 1] > hi) {
                hi = cmp_size[ncmp - 1];
                at = v;
            }
        }
    }

    dfs2(at, -1);
    printf("%d\n", hi);
    for (int i = 0; i < m; i++) {
        int u, v;
        tie(u, v) = edges[i];
        if (ans.find(edges[i]) != ans.end())
            printf("%d %d\n", u, v);
        else if (ans.find(pii(v, u)) != ans.end())
            printf("%d %d\n", v, u);
        else abort();
    }    
    return 0;
}
