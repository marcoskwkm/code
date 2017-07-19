#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)5e5 + 10;

/* A directed graph */
struct Graph {
    int V;
    vector<vector<int>> adj;
    
    Graph(int _V) : V(_V) {
        adj.resize(V);
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
    }
};

vector<pii> subtrees[MAXN];
int depth[MAXN];
int dfs_l[MAXN], dfs_r[MAXN];
int prv[MAXN];
int dfs_cnt;

// Fucking iterative DFS because recursion was overflowing stack
void dfs(int s, const Graph &g) {
    depth[s] = 0;
    stack<int> st;
    st.push(s);
    prv[s] = -1;
    while (!st.empty()) {
        int v = st.top();
        if (dfs_l[v] != -1) {
            st.pop();
            dfs_r[v] = dfs_cnt++;
        }
        else {
            dfs_l[v] = dfs_cnt++;
            for (int nxt: g.adj[v]) {
                if (nxt == prv[v]) continue;
                depth[nxt] = depth[v] + 1;
                st.push(nxt);
                prv[nxt] = v;
            }
        }
    }
}

int bit[2 * MAXN];

void bit_update(int i, int val) {
    i++;
    for (; i < 2 * MAXN; i += i & -i)
        bit[i] += val;
}

int bit_query(int i) {
    i++;
    int ret = 0;
    for (; i > 0; i -= i & -i)
        ret += bit[i];
    return ret;
}                

int main() {
    int n;
    cin >> n;
    Graph g(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        g.add_edge(u, v);
        g.add_edge(v, u);
    }
    memset(dfs_l, -1, sizeof(dfs_l));
    dfs_cnt = 0;
    dfs(1, g);
    for (int v = 1; v <= n; v++) {
        for (int nxt: g.adj[v]) {
            if (nxt == prv[v]) continue;
            subtrees[v].push_back(pii(dfs_l[nxt], dfs_r[nxt]));
        }
        sort(subtrees[v].begin(), subtrees[v].end());
    }
    
    int m;
    for (cin >> m; m--;) {
        int q;
        vector<int> s;
        for (scanf("%d", &q); q--;) {
            int v;
            scanf("%d", &v);
            s.push_back(v);
            bit_update(dfs_l[v], 1);
        }
        int n_leaves = 0;
        if (s.size() > 1) {
            int highest = s[0];
            for (int v: s) {
                if (depth[v] < depth[highest])
                    highest = v;
                if (bit_query(dfs_r[v]) - bit_query(dfs_l[v] - 1) == 1)
                    n_leaves++;
            }
            int ll = dfs_l[highest], rr = dfs_r[highest];
            for (int v: s) {
                if (v == highest) continue;
                if (dfs_r[v] < dfs_l[highest] || dfs_l[v] > dfs_r[highest]) {
                    rr = -1;
                    break;
                }
                pii subtree = *prev(lower_bound(subtrees[highest].begin(),
                                                subtrees[highest].end(),
                                                pii(dfs_l[v], INF)));
                ll = max(ll, subtree.first);
                rr = min(rr, subtree.second);
            }
            if (ll <= rr) n_leaves++;
        }
        printf("%d\n", (n_leaves + 1) / 2);
        for (int v: s)
            bit_update(dfs_l[v], -1);
    }            
    return 0;
}
