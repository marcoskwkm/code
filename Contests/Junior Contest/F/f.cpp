#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e6 + 10;
const int MAXND = (int)1e7 + 10;

int w[MAXN];
vector<int> adj[MAXN];
int prv[MAXN];
int depth[MAXN];

// trie
int q[MAXND];
int nxt[MAXND][2];
int size = 1;

void trie_add(int node, int i, int x) {
    q[node]++;
    if (i < 0) return;
    int to = 0;
    if (x & (1 << i)) to = 1;
    if (nxt[node][to] == 0)
        nxt[node][to] = ++size;
    trie_add(nxt[node][to], i - 1, x);
}

int trie_query(int node, int i, int x, int k) {
    if (node == 0) return 0;
    if (i < 0) return q[node];
    int low = 0;
    if (x & (1 << i)) low = 1;
    if (k & (1 << i))
        return trie_query(nxt[node][low ^ 1], i - 1, x, k);
    else
        return q[nxt[node][low ^ 1]] + trie_query(nxt[node][low], i - 1, x, k);
}

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%d", &w[i]);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    memset(depth, -1, sizeof(depth));
    queue<int> fila;
    depth[1] = 0;
    fila.push(1);
    while (!fila.empty()) {
        int v = fila.front();
        fila.pop();
        for (int to: adj[v]) {
            if (depth[to] == -1) {
                depth[to] = depth[v] + 1;
                prv[to] = v;
                fila.push(to);
            }
        }
    }

    int x, y;
    scanf("%d%d", &x, &y);
    vector<int> v;
    stack<int> st;
    while (x != y) {
        if (depth[x] >= depth[y]) {
            v.push_back(x);
            x = prv[x];
        }
        else {
            st.push(y);
            y = prv[y];
        }
    }
    v.push_back(x);
    while (!st.empty()) {
        v.push_back(st.top());
        st.pop();
    }
    int xr = 0;
    trie_add(1, 30, xr);
    lint ans = 0;
    for (int i: v) {
        xr ^= w[i];
        int add = trie_query(1, 30, xr, k);
        ans += add;
        trie_add(1, 30, xr);
    }
    cout << ans << endl;        
    return 0;
}
