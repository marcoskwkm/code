#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

const double EPS = 1e-12;

typedef double CTYPE;

//( cmp(a,b) _ 0 ) means (a _ b)
inline int cmp(double a, double b = 0) { return (a < b + EPS) ? (a + EPS < b) ? -1 : 0 : 1; }

struct Point {
    int color;
    double x, y;
    Point() {}
    Point (double xx, double yy) { x = xx, y = yy; }
    int _cmp(Point q) const {
        if (int t = cmp(x, q.x)) return t;
        return cmp(y, q.y);
    }
    bool operator==(Point q) const { return _cmp(q) == 0; }
    bool operator!=(Point q) const { return _cmp(q) != 0; }
    bool operator<(Point q) const { return _cmp(q) < 0; }    
};

typedef Point Vector;
typedef vector<Point> Poly;

double norm(Point &p) { return sqrt(p.x*p.x + p.y*p.y); }
Point operator*(double k, const Point &p) { return Point(k*p.x, k*p.y); }
Point operator/(const Point &p, double k) { return Point(p.x / k, p.y / k); }
Point operator+(const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y); }
Point operator-(const Point &a, const Point &b) { return Point(a.x-b.x, a.y-b.y); }
CTYPE operator*(const Point &a, const Point &b) { return a.x*b.x + a.y*b.y; }
CTYPE operator^(const Point &a, const Point &b) { return a.x*b.y - a.y*b.x; }

// Returns the intersection of lines pq and rs. Assumes pq and rs are not parallel.
Point getIntersection(const Point &p, const Point &q, const Point &r, const Point &s) {
    Point a = q - p, b = s - r, c = Point(p ^ q, r ^ s);
    assert(cmp(a ^ b));
    return Point(Point(a.x, b.x) ^ c, Point(a.y, b.y) ^ c) / (a ^ b);
}

Point get_intersection(const Point &p, const Vector &u, const Point &q, const Vector &v) {
    Point pp = p + u, qq = q + v;
    return getIntersection(p, pp, q, qq);
}

inline double dist(const Point &p, const Point &q) {
    Point pp = p - q;
    return norm(pp);
}

bool is_parallel(const Point &p, const Point &q, const Point &r) {
    Vector u = p - q, v = r - q;
    return cmp(u ^ v) == 0;
}

const int MAXN = 2010;

Point p[MAXN];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        cin >> p[i].x >> p[i].y;
        p[i].color = 1;
    }
    for (int i = n; i < n + m; i++) {
        cin >> p[i].x >> p[i].y;
        p[i].color = 0;
    }

    for (int i = 0; i < n + m; i++) {
        for (int j = 0; j < n + m; j++) {
            if (i == j) continue;
            double l = -LINF, hi = LINF;
            Vector dir = p[i] - p[j];
            Point M = (p[i] + p[j]) / 2;
            bool ok = 1;
            
            for (int k = n; k < n + m; k++) {
                if (k == i || k == j) continue;
                Vector u = p[k] - p[i], v = p[k] - p[j];
                if ((u ^ v) == 0) {
                    if (norm(u) < norm(dir) || norm(v) < norm(dir)) {
                        ok = 0;
                        break;
                    }
                    continue;
                }
                Point m = (p[i] + p[k]) / 2;
                Vector d = p[k] - p[i];
                Vector orth_d(d.y, -d.x);
                Point inter = get_intersection(M, orth_dir, m, orth_d);
                Vector bb = inter - M;
                double k = norm(bb);
                if ((dir ^ bb) < 0) k = -k;
                if ((dir ^ d) > 0) r = min(r, k);
                
    
    return 0;
}
