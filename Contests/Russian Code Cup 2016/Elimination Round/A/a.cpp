#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int n, t, t0;
    scanf("%d%d%d", &n, &t, &t0);
    while (n--) {
        int m;
        scanf("%d", &m);
        int hi = 0, ans = 0;
        int sum = 0;
        for (int i = 0; i < m; i++) {
            int ti;
            scanf("%d", &ti);
            hi = max(hi, ti);
            sum += ti;
            int needs = min(sum, sum - hi + t0);
            if (needs <= t) ans = i + 1;
        }
        printf("%d\n", ans);
    }
            
    return 0;
}
