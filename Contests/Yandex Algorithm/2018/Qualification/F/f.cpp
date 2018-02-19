// AC

#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)2e5 + 10;

vector<int> adj[MAXN];
int dist[MAXN];
int prv[MAXN];
bool in_diam[MAXN];
int diam[MAXN];
int diam_v[MAXN];
int n;

void bfs(vector<int> sv) {
    memset(prv, -1, sizeof(prv));
    queue<int> q;
    for (int s: sv) {
        dist[s] = 0;
        prv[s] = s;
        q.push(s);
    }
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int nxt: adj[v]) {
            if (prv[nxt] == -1) {
                prv[nxt] = v;
                dist[nxt] = dist[v] + 1;
                q.push(nxt);
            }
        }
    }
}

int get_val(int v, int p = -1) {
    int ret = 0;
    for (int nxt: adj[v]) {
        if (in_diam[nxt] || nxt == p) continue;
        ret = max(ret, 1 + get_val(nxt, v));
    }
    return ret;
}
    
pii solve(int d, int sz) {
    int l = INF;
    for (int i = 0; i < sz; i++) {
        if (diam_v[i] > d) return pii(-1, -1);
        l = min(l, i + d - diam_v[i]);
    }
    if (l < 0) return pii(-1, -1);
    if (l >= sz - 1) return pii(sz - 1, sz - 1);
    
    int r = -1;
    for (int i = 0; i < sz; i++)
        r = max(r, i - d + diam_v[i]);

    for (int i = l + 1; i <= r - 1; i++)
        if (min(i - l, r - i) + diam_v[i] > d)
            return pii(-1, -1);

    if (l == r) {
        if (r + 1 < sz) r++;
        else r--;
    }
    return pii(l, r);
}

int main() {
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    bfs({1});
    int head = 1;
    for (int v = 2; v <= n; v++)
        if (dist[v] > dist[head])
            head = v;
    bfs({head});
    int tail = 1;
    for (int v = 2; v <= n; v++)
        if (dist[v] > dist[tail])
            tail = v;

    int sz = 0;
    int cur = tail;
    diam[sz++] = cur;
    in_diam[cur] = 1;
    do {
        cur = prv[cur];
        diam[sz++] = cur;
        in_diam[cur] = 1;
    } while (cur != head);

    for (int i = 0; i < sz; i++)
        diam_v[i] = get_val(diam[i]);

    int l = 0, r = n;
    while (l < r) {
        int mid = (l + r) / 2;
        pii sol = solve(mid, sz);
        if (sol.first != -1) r = mid;
        else l = mid + 1;
    }

    // for (int i = 0; i < sz; i++)
    //     debug("%d(%d) ", diam[i], diam_v[i]);
    // debug("\n");
    
    // debug("maxd = %d\n", l);
    pii sol = solve(l, sz);

    printf("%d %d\n", diam[sol.first], diam[sol.second]);
    return 0;
}
