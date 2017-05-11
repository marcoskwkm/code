#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)2e5 + 10;

set<pii> prices[5];
int p[MAXN], a[MAXN], b[MAXN];

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        scanf("%d", &p[i]);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    for (int i = 0; i < n; i++) {
        scanf("%d", &b[i]);
        prices[a[i]].insert(pii(p[i], i));
        prices[b[i]].insert(pii(p[i], i));
    }

    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        if (i) printf(" ");
        int q;
        scanf("%d", &q);
        if (prices[q].empty()) printf("-1");
        else {
            pii p = *prices[q].begin();
            printf("%d", p.first);
            prices[a[p.second]].erase(p);
            prices[b[p.second]].erase(p);
        }
    }
    printf("\n");        
    return 0;
}
