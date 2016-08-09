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
    vector< pair<Point, Point> > edges;
    for (int i = 0; i < n; i++) {
        int j = (i + 1 == n ? 0 : i + 1);
        if (poly[i].y == poly[j].y) continue;
        if (poly[i].y < poly[j].y) edges.push_back(make_pair(poly[i], poly[j]));
        else edges.push_back(make_pair(poly[j], poly[i]));
    }

    int ans = 0;
    while (m--) {
        Point p;
        p.read();
        int add = 0;
        bool force = 0;
        for (auto &pp: edges) {
            Vector u = pp.second - pp.first;
            if (p.y < pp.first.y || p.y > pp.second.y) continue;
            if (p.y == pp.first.y) {
                if (p.x < pp.first.x) add ^= 1;
                else if (p.x == pp.first.x) force = 1;                    
                continue;
            }
            if (p.y == pp.second.y) {
                if (p.x < pp.second.x) add ^= 1;
                else if (p.x == pp.second.x) force = 1;
                continue;
            }                
            Vector v = p - pp.first;
            if ((u ^ v) == 0) force = 1;
            else if ((u ^ v) > 0) add ^= 1;
            if (force) break;
        }
        if (force || add) ans++;
    }
    printf("%d\n", ans);
        
    return 0;
}
