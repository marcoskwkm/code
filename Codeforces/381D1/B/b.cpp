#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)2e5 + 10;
const int LOG = 20;

vector<pii> adj[MAXN];
int a[MAXN];

int contr_by[MAXN];
vector<lint> st;
int up[LOG][MAXN];

void dfs(int v, int prv_cst, lint sum) {
    int l = 0, r = st.size();
    while (l < r) {
        int mid = (l + r) / 2;
        if (sum - st[mid] > a[v]) l = mid + 1;
        else r = mid;
    }
    contr_by[v] = st.size() - l;
    // printf("contr_by[%d] = %d\n", v, contr_by[v]);

    st.push_back(sum);
    for (pii edge: adj[v]) {
        up[0][edge.first] = v;
        dfs(edge.first, edge.second, sum + edge.second);
    }
    st.pop_back();
}

int go_up(int v, int q) {
    for (int i = LOG - 1; i >= 0; i--) {
        if (q >= (1 << i)) {
            v = up[i][v];
            q -= (1 << i);
        }
    }
    return v;
}

int ans[MAXN];
int rem[MAXN];

int go(int v) {
    int val = 0;
    for (pii edge: adj[v])
        val += go(edge.first);

    val -= rem[v];
    ans[v] = val;
    int anc = go_up(v, contr_by[v] + 1);
    if (go_up(v, contr_by[v]) != anc)
        rem[anc]++;
    return val + 1;
}    

int main() {
    int n;
    scanf("%d", &n);
    for (int v = 1; v <= n; v++)
        scanf("%d", &a[v]);
    for (int v = 2; v <= n; v++) {
        int p, c;
        scanf("%d%d", &p, &c);
        adj[p].push_back(pii(v, c));
    }

    up[0][1] = 1;
    dfs(1, 0, 0);
    for (int i = 1; i < LOG; i++)
        for (int v = 1; v <= n; v++)
            up[i][v] = up[i - 1][up[i - 1][v]];

    go(1);
    for (int v = 1; v <= n; v++)
        printf("%d%c", ans[v], v == n ? '\n' : ' ');
    
    return 0;
}
