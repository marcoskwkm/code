const double EPS = 1e-9;
const double PI = acos(-1.0);

typedef int CTYPE;

//( cmp(a,b) _ 0 ) means (a _ b)
inline int cmp(double a, double b = 0) {
    return (a < b + EPS) ? (a + EPS < b) ? -1 : 0 : 1;
}

struct Point {
    CTYPE x,y;
    Point() {}
    Point(CTYPE xx,CTYPE yy) { x = xx; y = yy; }
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

double norm(Vector &v) { return sqrt(v.x * v.x + v.y * v.y); }
Vector operator*(double k, const Vector &v) { return Vector(k * v.x, k * v.y); }
Vector operator/(const Vector &v, double k) { return Vector(v.x / k, v.y / k); }
Point operator+(const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y); }
Point operator-(const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
CTYPE operator*(const Vector &u, const Vector &v) { return u.x * v.x + u.y * v.y; }
CTYPE operator^(const Vector &u, const Vector &v) { return u.x * v.y - u.y * v.x; }

// SIGNED area
double area(vector<Point>& polygon) {
    double ret = 0;
    int n = polygon.size();
    for(int i = 0; i < n; ++i) {
        int j = (i == n - 1 ?  0 : i + 1);
        ret += polygon[i] ^ polygon[j];
    }
    return 0.5 * ret;
}

// finds polygon centroid (needs SIGNED area)
double centroid(vector<Point>& polygon) {
    double S = area(polygon);
    double ret = 0;
    int n = polygon.size();
    for (int i = 0; i < n; ++i) {
        int j = (i == n-1 ? 0 : i + 1);
        ret += (polygon[i].x + polygon[j].x) * (polygon[i] ^ polygon[j]);
    }
    return ret / 6 / S;
}

// Distance from r to segment pq
double point_seg_dist(const Point &r, const Point &p, const Point &q) {
    Point A = r-q, B = r-p, C = q-p;
    double a = A*A, b = B*B, c = C*C;
    if(cmp(b, a+c) >= 0) return sqrt(a);
    else if(cmp(a, b+c) >= 0) return sqrt(b);
    else return fabs(A^B)/sqrt(c);
}

// Whether segments pq and rs have a common point
bool seg_intersects(const Point &p, const Point &q, const Point &r, const Point &s) {
    Point A = q - p, B = s - r, C = r - p, D = s - q;
    int a = cmp(A ^ C) + 2 * cmp(A ^ D);
    int b = cmp(B ^ C) + 2 * cmp(B ^ D);
    if (a == 3 || a == -3 || b == 3 || b == -3) return false;
    if (a || b || p == r || p == s || q == r || q == s) return true;
    int t = (p < r) + (p < s) + (q < r) + (q < s);
    return t != 0 && t != 4;
}

// Returns the intersection of lines pq and rs. Assumes pq and rs are not parallel.
Point intersection(const Point &p, const Point &q, const Point &r, const Point &s) {
    Point a = q - p, b = s - r, c = Point(p ^ q, r ^ s);
    assert(cmp(a ^ b));
    return Point(Point(a.x, b.x) ^ c, Point(a.y, b.y) ^ c) / (a ^ b);
}

// Returns convex hull in clockwise-order.
Poly convex_hull(vector<Point> poly) {
    sort(poly.begin(), poly.end(), [](const Point &a, const Point &b) {
        if (a.x == b.x) return a.y < b.y;
        return a.x < b.x;
    });
    Poly top, bot;
    int tlen = 0, blen = 0;
    for (const Point &p: poly) {
        while (tlen > 1 &&
               ((top[tlen - 2] - top[tlen - 1])^(p - top[tlen - 1])) <= 0) {
            tlen--;
            top.pop_back();
        }
        while (blen > 1 &&
               ((p - bot[blen - 1])^(bot[blen - 2] - bot[blen - 1])) <= 0) {
            blen--;
            bot.pop_back();
        }
        top.push_back(p);
        bot.push_back(p);
        tlen++;
        blen++;
    }
    for (int i = blen - 2; i > 0; i--)
        top.push_back(bot[i]);
    return top;
}

// Checks whether given point is inside a convex polygon.
// Assumes polygon vertices are given in CCW order.
bool in_polygon(const Point &p, const Poly &poly) {
    Vector vp = p - poly[0];
    if (((poly[1] - poly[0]) ^ vp) < 0) return 0;
    int l = 1, r = poly.size() - 1;
    while (l < r) {
        int mid = (l + r + 1) / 2;
        if (((poly[mid] - poly[0]) ^ vp) > 0) l = mid;
        else r = mid - 1;
    }
    if (l == (int)poly.size() - 1) return 0;
    return ((poly[l + 1] - poly[l]) ^ (p - poly[l])) > 0;
}
