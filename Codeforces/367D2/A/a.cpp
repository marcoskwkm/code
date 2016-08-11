#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int x, y;
    scanf("%d%d", &x, &y);
    double ans = LINF;
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int xx, yy, v;
        scanf("%d%d%d", &xx, &yy, &v);
        ans = min(ans, (double)hypot(xx - x, yy - y) / v);
    }
    printf("%.10f\n", ans);
    return 0;
}
