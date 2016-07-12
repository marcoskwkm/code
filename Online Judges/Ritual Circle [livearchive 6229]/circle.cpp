#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const double EPS = 1e-12;

typedef double CTYPE;

//( cmp(a,b) _ 0 ) means (a _ b)
inline int cmp(double a, double b = 0) { return (a < b + EPS) ? (a + EPS < b) ? -1 : 0 : 1; }

struct Point {
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

Point parse(string s) {
    int x, y;
    sscanf(s.c_str(), "%*c%d%*c%d", &x, &y);
    return Point(x, y);
}

inline void read_input(vector<Point> &v, string line) {
    stringstream ss(line);
    string point;
    ss >> point; // trash
    while (!ss.eof()) {
        ss >> point;
        if (point == "none") break;
        v.push_back(parse(point));
    }
}

int main() {
    int t = 0;
    while (1) {
        t++;
        string line;
        if (!getline(cin, line)) break;
        vector<Point> good, bad;
        read_input(good, line);
        getline(cin, line);
        read_input(bad, line);

        int ng = good.size(), nb = bad.size();
        if (ng <= 1) {
            printf("0\n");
            continue;
        }
        // if (t == 10) printf("%d %d\n", ng, nb);

        bool found = 0;
        double ans = LINF;
        for (int i = 0; i < ng; i++) {
            for (int j = i + 1; j < ng; j++) {
                Point p = good[i], q = good[j];
                Point M = (p + q) / 2;
                Vector dir = p - q;
                Vector orth_dir(dir.y, -dir.x);
                bool ok = 1;
                double low = -LINF, hi = LINF;
                
                for (const Point &g: good) {
                    if (p == g || p == q) continue;
                    if (is_parallel(p, q, g)) {
                        Vector u = g - p, v = g - q;
                        if (norm(u) > norm(dir) || norm(v) > norm(dir)) {
                            ok = 0;
                            break;
                        }
                        continue;
                    }
                    Point m = (p + g)/2;
                    Vector d = g - p;
                    Vector orth_d(d.y, -d.x);
                    Point inter = get_intersection(M, orth_dir, m, orth_d);

                    Vector gg = inter - M;
                    double k = norm(gg);
                    if ((dir ^ gg) < 0) k = -k;
                    if ((dir ^ d) > 0) low = max(low, k);
                    else hi = min(hi, k);
                }
                for (const Point &b: bad) {
                    if (is_parallel(p, q, b)) {
                        Vector u = b - p, v = b - q;
                        if (norm(u) < norm(dir) || norm(v) < norm(dir)) {
                            ok = 0;
                            break;
                        }
                        continue;
                    }
                    Point m = (p + b)/2;
                    Vector d = b - p;
                    Vector orth_d(d.y, -d.x);
                    Point inter = get_intersection(M, orth_dir, m, orth_d);
                    // if (t == 10) printf("(%.0f, %.0f) -> (%.2f, %.2f)\n", b.x, b.y,
                    //        inter.x, inter.y);

                    Vector bb = inter - M;
                    double k = norm(bb);
                    if ((dir ^ bb) < 0) k = -k;
                    if ((dir ^ d) > 0) hi = min(hi, k - 2*EPS);
                    else low = max(low, k + 2*EPS);
                }

                if (!ok) continue;
                // if (t == 10) printf("%.2f - %.2f\n", low, hi);
                if (low <= hi) {
                    double h;
                    if (hi < 0) h = -hi;
                    else if (low > 0) h = low;
                    else h = 0;
                    orth_dir = orth_dir / norm(orth_dir);
                    Point center = M + h*orth_dir;
                    Point radii = p - center;
                    ans = min(ans, norm(radii));
                    found = 1;
                }
            }
        }
        if (!found) printf("The Orcs are close\n");
        else printf("%.15f\n", ans);
    }
    return 0;
}
