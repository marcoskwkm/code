#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int n;
    scanf("%d", &n);
    int l = -INF, r = INF;
    int delta = 0;
    for (int i = 0; i < n; i++) {
        int var, div;
        scanf("%d%d", &var, &div);
        if (div == 1) l = max(l, 1900 - delta);
        else r = min(r, 1899 - delta);
        delta += var;
    }
    if (l > r) printf("Impossible\n");
    else if (r == INF) printf("Infinity\n");
    else printf("%d\n", r + delta);            
    return 0;
}
