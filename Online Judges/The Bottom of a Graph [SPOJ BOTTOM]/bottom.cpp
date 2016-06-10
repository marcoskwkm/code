#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5010;

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

bool dont[MAXN];

int main() {
    int n, m;
    while (scanf("%d", &n) > 0 && n) {
        scanf("%d", &m);
        for (int v = 1; v <= n; v++) adj[v].clear();
        for (int i = 0; i < m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            adj[u].push_back(v);
        }
        Tarjan::init();
        for (int v = 1; v <= n; v++)
            if (Tarjan::ind[v] == -1)
                Tarjan::tarjan(v);
        vector<int> ans;
        memset(dont, 0, sizeof(dont));
        for (int v = 1; v <= n; v++) {
            for (int nxt: adj[v]) {
                if (Tarjan::cmp[nxt] != Tarjan::cmp[v])
                    dont[Tarjan::cmp[v]] = 1;
            }
        }
        for (int v = 1; v <= n; v++)
            if (!dont[Tarjan::cmp[v]])
                ans.push_back(v);
        for (int i = 0; i < (int)ans.size(); i++)
            printf("%d%c", ans[i], " \n"[i + 1 == ans.size()]);
    }        
    return 0;
}
