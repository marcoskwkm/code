#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 100;

pll operator+(const pll &a, const pll &b) {
    return pll(a.first + b.first, a.second + b.second);
}

vector<int> adj[MAXN];
int t[MAXN];

pll go(int v, lint k = 1) {
    pll ret(t[v], t[v] * k);
    for (int nxt: adj[v])
        ret = ret + go(nxt, 2 * k);
    return ret;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int u = 1; u <= n; u++)
        scanf("%d", &t[u]);
    for (int u = 1; u <= n; u++) {
        int q;
        for (scanf("%d", &q); q--;) {
            int v;
            scanf("%d", &v);
            adj[u].push_back(v);
        }
    }
    pll ans = go(1);
    printf("%lld %lld\n", ans.first, ans.second);            
    return 0;
}
