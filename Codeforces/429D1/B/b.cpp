 #include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)3e5 + 10;

vector<pii> adj[MAXN];
int d[MAXN];
bool seen[MAXN];

int dfs(int v, int idx, set<int> &sol) {
    seen[v] = 1;
    int cnt = (d[v] != -1 && d[v] % 2 != (int)adj[v].size() % 2);
    for (pii edge: adj[v]) {
        int nxt, id;
        tie(nxt, id) = edge;
        if (seen[nxt]) continue;
        cnt += dfs(nxt, id, sol);
    }
    cnt %= 2;
    if (cnt) sol.erase(idx);
    return cnt;
}    

int main() {
    int n, m;
    cin >> n >> m;
    int minus_one = -1;
    for (int v = 1; v <= n; v++) {
        scanf("%d", &d[v]);
        if (d[v] == -1) minus_one = v;
    }
    set<int> sol;
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(pii(v, i + 1));
        adj[v].push_back(pii(u, i + 1));
        sol.insert(i + 1);
    }
    int cnt = 0;
    for (int v = 1; v <= n; v++) {
        if (d[v] == -1) continue;
        if ((int)adj[v].size() % 2 != d[v]) cnt++;
    }
    if (cnt & 1) {
        if (minus_one == -1) {
            printf("-1\n");
            return 0;
        }
        else d[minus_one] = ((int)adj[minus_one].size() + 1) % 2;
    }
    
    assert(dfs(1, -1, sol) == 0);
    // dfs(1, -1, sol);
    printf("%d\n", (int)sol.size());
    for (int x: sol) printf("%d\n", x);
    return 0;
}
