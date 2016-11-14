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
int ncomp[MAXN];

int main() {
    int n, m, a, b;
    scanf("%d%d%d%d", &n, &m, &a, &b);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    set<pii> lo;
    set< pii, greater<pii> > hi;
    for (int i = 1; i <= n; i++) {
        ncomp[i] = adj[i].size();
        lo.insert(pii(ncomp[i], i));
        hi.insert(pii(ncomp[i], i));
    }

    int ans = n;
    while (ans > 0) {
        if (lo.begin()->first < a) {
            ans--;
            int rem = lo.begin()->second;
            lo.erase(lo.begin());
            hi.erase(pii(ncomp[rem], rem));
            for (int nxt: adj[rem]) {
                if (lo.find(pii(ncomp[nxt],nxt)) == lo.end()) continue;
                lo.erase(pii(ncomp[nxt], nxt));
                hi.erase(pii(ncomp[nxt], nxt));
                ncomp[nxt]--;
                lo.insert(pii(ncomp[nxt], nxt));
                hi.insert(pii(ncomp[nxt], nxt));
            }
        }
        
        else if (ans - 1 - hi.begin()->first < b) {
            ans--;
            int rem = hi.begin()->second;
            hi.erase(hi.begin());
            lo.erase(pii(ncomp[rem], rem));
            for (int nxt: adj[rem]) {
                if (lo.find(pii(ncomp[nxt],nxt)) == lo.end()) continue;
                lo.erase(pii(ncomp[nxt], nxt));
                hi.erase(pii(ncomp[nxt], nxt));
                ncomp[nxt]--;
                lo.insert(pii(ncomp[nxt], nxt));
                hi.insert(pii(ncomp[nxt], nxt));
            }
        }
        else break;
    }
    
    printf("%d\n", ans);    
    return 0;
}
