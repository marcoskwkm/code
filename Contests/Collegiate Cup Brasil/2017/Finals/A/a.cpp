#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e4 + 10;

int nxt[MAXN];
bool in[MAXN];
bool seen[MAXN];

bool dfs(int v) {
    seen[v] = 1;
    if (!in[v]) return 0;
    if (!seen[nxt[v]]) return dfs(nxt[v]);
    return 1;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int v = 1; v <= n; v++)
        scanf("%d", &nxt[v]);
    int s, c;
    scanf("%d%d", &s, &c);
    while (s--) {
        memset(in, 0, sizeof(in));
        vector<int> v(c);
        for (int i = 0; i < c; i++) {
            scanf("%d", &v[i]);
            in[v[i]] = 1;
        }
        memset(seen, 0, sizeof(seen));
        bool ok = 1;
        for (int x: v)
            if (!dfs(x))
                ok = 0;
        printf("%s\n", ok ? "yes" : "no");
    }    
    return 0;
}
