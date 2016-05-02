#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef pair<int, lint> pil;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 20;

lint w[MAXN], c[MAXN];

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++)
            scanf("%lld", &w[i]);
        for (int i = 1; i <= n; i++)
            scanf("%d", &c[i]);
    }    
    return 0;
}
