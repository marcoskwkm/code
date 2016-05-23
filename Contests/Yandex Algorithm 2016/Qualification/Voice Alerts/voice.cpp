#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    double v, t;
    scanf("%lf%lf", &v, &t);
    int n;
    scanf("%d", &n);
    double low = LINF;
    int idx;
    for (int i = 1; i <= n; i++) {
        double d, T;
        scanf("%lf%lf", &d, &T);
        double got = d + (T + t)*v;
        if (got < low) {
            low = got;
            idx = i;
        }
    }
    printf("%.5f %d\n", low, idx);
    return 0;
}
