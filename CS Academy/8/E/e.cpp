#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;

vector<int> adj[MAXN];
int score[MAXN];
lint best[2][MAXN];

void dfs(int v, int prv) {
    multiset<lint, greater<lint>> ms;
    for (int nxt: adj[v]) {
        if (nxt == prv) continue;
        dfs(nxt, v);
        ms.insert(best[1][nxt]);
    }
    best[0][v] = score[0];
    best[1][v] = score[1];
    lint sum = 0;
    auto it = ms.begin();
    for (int take = 1; it != ms.end(); take++) {
        sum += *it;
        best[0][v] = max(best[0][v], sum + score[take]);
        best[1][v] = max(best[1][v], sum + score[take + 1]);
        it++;
    }
    // printf("best[0][%d] = %lld, best[1][%d] = %lld\n", v, best[0][v], v, best[1][v]);
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", &score[i]);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, 0);
    lint ans = score[0];
    for (int v = 1; v <= n; v++)
        ans = max(ans, best[0][v]);

    printf("%lld\n", ans);    
    return 0;
}
