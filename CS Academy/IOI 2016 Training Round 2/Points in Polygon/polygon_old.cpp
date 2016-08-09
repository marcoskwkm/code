#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const float PI = acos(-1.0);
const float eps = 1e-2;
const int MAXN = 2010;

struct Point {
    lint x, y;
    Point (lint xx = 0, lint yy = 0) { x = xx, y = yy; }
    void read() { scanf("%lld%lld", &x, &y); }
};

typedef Point Vector;

Vector operator-(Point a, Point b) { return Point(a.x-b.x, a.y-b.y); }
inline lint operator* (Vector u, Vector v) { return u.x*v.x + u.y*v.y; }
inline lint operator^ (Vector u, Vector v) { return u.x*v.y - u.y*v.x; }

Point poly[MAXN];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        poly[i].read();
    reverse(poly, poly + n);

    int ans = 0;
    while (m--) {
        Point p;
        p.read();
        float sum = 0;
        for (int i = 0; i < n; i++) {
            int nxt = (i + 1 == n ? 0 : i + 1);
            Vector u = poly[i] - p, v = poly[nxt] - p;
            lint s = u ^ v, c = u * v;
            float angle;
            if (c == 0) {
                if (s > 0) angle = PI / 2;
                else angle = -PI / 2;
            }
            else angle = atan(float(s) / c);
            if (c < 0) {
                if (s > 0) angle += PI;
                else if (s < 0) angle -= PI;
            }
            sum += angle;
            // sum += atan2(u ^ v, u * v);
            // printf("got: %.2f, real: %.2f\n", angle, atan2(s, c));
        }
        if (fabs(sum) > eps) ans++;
    }
    printf("%d\n", ans);
        
    return 0;
}
