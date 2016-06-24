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

namespace Tarjan {
    int cmp[MAXN]; // component of [i]
    int cnt;       // number of components
    int ind[MAXN], low[MAXN], pre;
    bool instack[MAXN];
    stack<int> st;

    void tarjan(int v) {
        ind[v] = low[v] = pre++;
        st.push(v);
        instack[v] = 1;
        for (int nxt: adj[v]) {
            if (ind[nxt] == -1) {
                tarjan(nxt);
                low[v] = min(low[v], low[nxt]);
            }
            else if (instack[nxt]) low[v] = min(low[v], ind[nxt]);
        }
        if (ind[v] == low[v]) {
            int vv;
            do {
                vv = st.top();
                st.pop();
                instack[vv] = 0;
                cmp[vv] = cnt;
            } while (vv != v);
            ++cnt;
        }
    }

    inline void init() {
        memset(ind, -1, sizeof(ind));
        pre = 0; cnt = 0;
    }
}

bool foo[MAXN];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
    }
    Tarjan::init();
    for (int v = 1; v <= n; v++)
        if (Tarjan::ind[v] == -1)
            Tarjan::tarjan(v);

    for (int v = 1; v <= n; v++)
        for (int nxt: adj[v])
            if (Tarjan::cmp[v] != Tarjan::cmp[nxt])
                foo[Tarjan::cmp[nxt]] = 1;
    int ans = 0;
    for (int v = 1; v <= n; v++)
        if (!foo[Tarjan::cmp[v]])
            ans++;
    printf("%d\n", ans);    
    return 0;
}
