#include <bits/stdc++.h>
using namespace std;

#define debug(args...) if (t == 4) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int DX = 2000;

long double calc_x(int x1, int y1, int x2, int y2, int y) {
    return ((long double)(y - y1) / (y2 - y1)) * (x2 - x1) + x1;
}

int main() {
    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        vector<pii> monster, proj;
        int n, m;
        cin >> n;
        for (int i = 0; i < n; i++) {
            int x, y;
            cin >> x >> y;
            monster.push_back(pii(x, y));
        }
        cin >> m;
        for (int i = 0; i < m; i++) {
            int x, y;
            cin >> x >> y;
            proj.push_back(pii(x, y));
        }

        long double ans = 0;
        for (int i = 0; i < n; i++) {
            int mx1, my1, mx2, my2;
            tie(mx1, my1) = monster[i];
            tie(mx2, my2) = monster[(i + 1) % n];
            int myh = max(my1, my2), myl = min(my1, my2);
            // debug("monster (%d, %d) -> (%d, %d)\n", mx1, my1, mx2, my2);
            for (int j = 0; j < m; j++) {
                int px1, py1, px2, py2;
                tie(px1, py1) = proj[j];
                tie(px2, py2) = proj[(j + 1) % m];
                // debug("proj (%d, %d) -> (%d, %d)\n", px1, py1, px2, py2);
                int pyh = max(py1, py2), pyl = min(py1, py2);
                int yh = min(myh, pyh), yl = max(myl, pyl);
                if (yh <= yl) continue;
                long double mxh = calc_x(mx1, my1, mx2, my2, yh);
                long double mxl = calc_x(mx1, my1, mx2, my2, yl);
                long double pxh = calc_x(px1, py1, px2, py2, yh);
                long double pxl = calc_x(px1, py1, px2, py2, yl);
                long double dxh = mxh - pxh, dxl = mxl - pxl;
                long double add = (long double)(yh - yl) / 6 * (dxh - dxl) * (dxh - dxl);
                long double area = 1./2 * fabs(dxh - dxl) * (yh - yl);
                // debug("preadd = %.3f, area = %.3f\n", add, area);
                // debug("dxh = %.3f, dxl = %.3f\n", dxh, dxl);
                long double rem = DX - max(dxh, dxl);
                add += 1./2 * rem * rem * (yh - yl) + area * rem;
                if (py2 < py1) add *= -1;
                if (my2 > my1) add *= -1;
                // debug("add = %.3f\n", add);
                ans += add;
            }
        }
        printf("Case %d: %.6Lf\n", t, ans);
    }                
    return 0;
}
