// small 1 and 2

#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 110;

int q[MAXN];
bool seen[MAXN];
vector<int> adj[MAXN];

void dfs(int v) {
    seen[v] = 1;
    if (!q[v]) {
        for (int nxt: adj[v])
            if (!seen[nxt])
                dfs(nxt);
    }
}

int main() {
    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            adj[i].clear();
            adj[i].push_back(u);
            adj[i].push_back(v);
        }
        for (int i = 1; i <= n; i++)
            scanf("%d", &q[i]);
        
        int ans = q[1];
        q[1] = 0;
        while (1) {
            memset(seen, 0, sizeof(seen));
            dfs(1);
            bool found = 0;
            for (int i = 1; i <= n; i++) {
                int u = adj[i][0], v = adj[i][1];
                if (u == v) {
                    if (seen[i] && !q[i] && q[u] >= 2) {
                        q[u] -= 2;
                        q[i]++;
                        found = 1;
                        break;
                    }
                }
                else {
                    if (seen[i] && !q[i] && q[u] && q[v]) {
                        q[u]--;
                        q[v]--;
                        q[i]++;
                        found = 1;
                        break;
                    }
                }
            }
            if (q[1]) {
                ans++;
                q[1] = 0;
            }
            if (!found) break;
        }            
        printf("Case #%d: %d\n", t, ans);
    }        
    return 0;
}
