#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e6 + 10;

int wins[MAXN];

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++)
            wins[i] = i - 1;
        for (int i = 0; i < m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            if (u > v) swap(u, v);
            wins[u]++, wins[v]--;
        }
        bool found = 0;
        for (int i = 1; i <= n; i++) {
            if (wins[i] == n - 1) {
                printf("2 %d\n", i);
                found = 1;
                break;
            }
        }
        if (!found) printf("1\n");
    }        
    return 0;
}
