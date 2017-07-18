#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 55;

int x[MAXN], y[MAXN], s[MAXN];
int n;

double get(double xx, double yy) {
    double ret = 0;
    for (int i = 0; i < n; i++)
        ret = max(ret, hypot(x[i] - xx, y[i] - yy) / s[i]);
    return ret;
}    

double go(double xx) {
    double yl = -1e9, yr = 1e9;
    for (int sy = 0; sy < 100; sy++) {
        double myl = (2*yl + yr) / 3, myr = (yl + 2*yr) / 3;
        double vl = get(xx, myl), vr = get(xx, myr);
        if (vl < vr) yr = myr;
        else yl = myl;
    }
    return get(xx, yl);
}

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d%d%d", &x[i], &y[i], &s[i]);
        double xl = -1e9, xr = 1e9;
        for (int sx = 0; sx < 100; sx++) {
            double mxl = (2*xl + xr) / 3, mxr = (xl + 2*xr) / 3;
            double vl = go(mxl), vr = go(mxr);
            if (vl < vr) xr = mxr;
            else xl = mxl;
        }
        printf("%.6f\n", go(xl));
    }            
    return 0;
}
