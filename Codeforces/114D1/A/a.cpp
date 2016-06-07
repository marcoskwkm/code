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
    double a, d;
    scanf("%d%lf%lf", &n, &a, &d);
    double last = 0;
    for (int i = 0; i < n; i++) {
        double t, v;
        scanf("%lf%lf", &t, &v);
        double tvmax = v / a;
        double tfulla = sqrt(2 * d / a);
        if (tvmax < tfulla) {
            double dist = a * tvmax*tvmax / 2;
            double rem = d - dist;
            double trem = rem / v;
            last = max(last, t + tvmax + trem);
        }
        else last = max(last, t + tfulla);
        printf("%.10f\n", last);
    }            
    return 0;
}
