#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;

vector<int> adj[MAXN];
int color[MAXN];
bool ok = 1;

void dfs(int v, int c) {
    color[v] = c;
    for (int nxt: adj[v]) {
        if (color[nxt] == -1) dfs(nxt, c ^ 1);
        else if (color[nxt] == c) ok = 0;
    }
}        

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    memset(color, -1, sizeof(color));
    for (int v = 1; v <= n; v++)
        if (color[v] == -1)
            dfs(v, 0);
    if (!ok) printf("-1\n");
    else {
        vector<int> ans[2];
        for (int v = 1; v <= n; v++)
            ans[color[v]].push_back(v);
        printf("%d\n", ans[0].size());
        for (int x: ans[0]) printf("%d\n", x);
        printf("%d\n", ans[1].size());
        for (int x: ans[1]) printf("%d\n", x);
    }    
    return 0;
}
