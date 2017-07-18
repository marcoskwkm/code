#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;

vector<int> adj[MAXN];
bool dead[MAXN];
int q[MAXN];

void dfs(int v, int prv, int cnt) {
    q[v] = cnt;
    for (int nxt: adj[v]) {
        if (nxt == prv) continue;
        dfs(nxt, v, cnt + dead[v]);
    }
}        

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) adj[i].clear();
        for (int i = 1; i < n; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        memset(dead, 0, sizeof(dead));
        int m;
        for (scanf("%d", &m); m--;) {
            int x;
            scanf("%d", &x);
            dead[x] = 1;
        }
        dfs(1, -1, 0);
        long double ans = n;
        for (int v = 1; v <= n; v++)
            ans -= (long double)1 / (1 + q[v]);
        printf("%.12Lf\n", ans);
    }            
    return 0;
}
