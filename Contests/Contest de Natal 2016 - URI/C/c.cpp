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
const int RT = 320;
const int LOG = 20;

int present[MAXN];
vector<int> adj[MAXN];

int order[2 * MAXN];
int pre[MAXN], pos[MAXN];
int depth[MAXN];
int up[LOG][MAXN];
int cnt;
void dfs(int v, int prv, int d = 0) {
    up[0][v] = prv;
    pre[v] = cnt;
    order[cnt++] = v;
    depth[v] = d;
    for (int nxt: adj[v]) {
        if (nxt == prv) continue;
        dfs(nxt, v, d + 1);
    }
    pos[v] = cnt;
    order[cnt++] = v;
}

struct Query {
    int l, r, i, lca;
    Query(int _l = 0, int _r = 0, int _i = 0, int _lca = 0)
        : l(_l), r(_r), i(_i), lca(_lca) {}
};

int ans[MAXN];

int get_lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    for (int i = LOG - 1; i >= 0; i--)
        if (depth[u] - (1 << i) >= depth[v])
            u = up[i][u];
    if (u == v) return u;
    for (int i = LOG - 1; i >= 0; i--)
        if (up[i][u] != up[i][v])
            u = up[i][u], v = up[i][v];
    return up[0][u];
}

int freq[MAXN];
int cur_pres[MAXN];

int cur_cnt;
inline void add(int i) {
    if (freq[i]++ > 0) {
        if (--cur_pres[present[i]] == 0) cur_cnt--;
    }
    else if (cur_pres[present[i]]++ == 0) cur_cnt++;    
}

inline void rem(int i) {
    if (--freq[i] == 1) {
        if (cur_pres[present[i]]++ == 0) cur_cnt++;
    }
    else if (--cur_pres[present[i]] == 0) cur_cnt--;
}

int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    map<string, int> mp;
    int sz = 0;
    for (int v = 1; v <= n; v++) {
        string p;
        cin >> p;
        if (mp.find(p) == mp.end())
            mp[p] = sz++;
        present[v] = mp[p];
    }

    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, 1);
    for (int i = 1; i < LOG; i++)
        for (int v = 1; v <= n; v++)
            up[i][v] = up[i - 1][up[i - 1][v]];

    vector<Query> queries;
    for (int i = 0; i < q; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        if (pre[u] > pre[v]) swap(u, v);
        int lca = get_lca(u, v);
        if (lca == u) queries.push_back(Query(pre[u], pre[v], i, lca));
        else queries.push_back(Query(pos[u], pre[v], i, lca));
    }
    sort(queries.begin(), queries.end(), [](Query a, Query b) {
        int bucket_a = a.l / RT, bucket_b = b.l / RT;
        if (bucket_a != bucket_b) return bucket_a < bucket_b;
        return a.r < b.r;
    });

    int cur_l = 0, cur_r = -1;
    for (Query query: queries) {
        while (cur_l < query.l) rem(order[cur_l++]);
        while (cur_l > query.l) add(order[--cur_l]);
        while (cur_r < query.r) add(order[++cur_r]);
        while (cur_r > query.r) rem(order[cur_r--]);

        int u = order[cur_l], v = order[cur_r];
        if (u != query.lca && v != query.lca) add(query.lca);
        ans[query.i] = cur_cnt;
        if (u != query.lca && v != query.lca) rem(query.lca);
    }            

    for (int i = 0; i < q; i++)
        printf("%d\n", ans[i]);
    return 0;
}
