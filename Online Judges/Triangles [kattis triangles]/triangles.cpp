#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const double EPS = 1e-9;

typedef double CTYPE;

struct Point {
    CTYPE x, y, z;
    Point(CTYPE xx = 0, CTYPE yy = 0, CTYPE zz = 0) {
        x = xx, y = yy, z = zz;
    }
};

typedef Point Vector;

double norm(const Vector &v) { return sqrt(v.x*v.x + v.y*v.y + v.z*v.z); }

Point operator+(const Point &p, const Vector &v) {
    return Point(p.x + v.x, p.y + v.y, p.z + v.z);
}

Vector operator-(const Point &p, const Point &q) {
    return Vector(p.x - q.x, p.y - q.y, p.z - q.z);
}

CTYPE operator*(const Vector &u, const Vector &v) {
    return u.x*v.x + u.y*v.y + u.z*v.z;
}

Vector operator*(CTYPE k, const Vector &v) {
    return Vector(k*v.x, k*v.y, k*v.z);
}

Vector operator^(const Vector &u, const Vector &v) {
    return Vector(u.y*v.z - u.z*v.y,
                  u.z*v.x - u.x*v.z,
                  u.x*v.y - u.y*v.x);
}
        
inline void read_point(Point &p) { scanf("%lf%lf%lf", &p.x, &p.y, &p.z); }

tuple<double, double, double, double> get_plane_equation(const Point &p1, const Point &p2, const Point &p3) {
    Vector u = p2 - p1, v = p3 - p1;
    Vector n = u ^ v;
    return make_tuple(n.x, n.y, n.z, -n.x*p1.x - n.y*p1.y - n.z*p1.z);
}

pair<Point, bool> get_line_plane_intersection(const Point &p1, const Point &p2,
                                              double a, double b, double c, double d) {
    Vector v = p2 - p1, n(a, b, c);
    double t = -(d + p1*n) / (v * n);
    Point p = p1 + t*v;
    bool intersects = (0 - EPS <= t && t <= 1 + EPS);
    return make_pair(p, intersects);
}

bool is_point_in_triangle(Point p, Point p1, Point p2, Point p3) {
    double area = norm((p2 - p1) ^ (p3 - p1));
    double got = norm((p - p1)^(p - p2)) + norm((p - p1)^(p - p3)) + norm((p - p2)^(p - p3));
    if (fabs(area - got) < EPS) return 1;
    return 0;
}

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        Point p1, p2, p3, q1, q2, q3;
        read_point(p1); read_point(p2); read_point(p3);
        read_point(q1); read_point(q2); read_point(q3);
        double a, b, c, d;
        tie(a, b, c, d) = get_plane_equation(p1, p2, p3);

        vector<Point> inters;
        bool intersects;
        Point p;
        tie(p, intersects) = get_line_plane_intersection(q1, q2, a, b, c, d);
        if (intersects) inters.push_back(p);
        // printf("inter1: (%.2f, %.2f, %.2f)\n", p.x, p.y, p.z);

        tie(p, intersects) = get_line_plane_intersection(q1, q3, a, b, c, d);
        if (intersects) inters.push_back(p);
        // printf("inter2: (%.2f, %.2f, %.2f)\n", p.x, p.y, p.z);

        tie(p, intersects) = get_line_plane_intersection(q2, q3, a, b, c, d);
        if (intersects) inters.push_back(p);
        // printf("inter3: (%.2f, %.2f, %.2f)\n", p.x, p.y, p.z);

        if (inters.empty()) printf("NO\n");
        else {            
            bool point_in = 0, point_out = 0;
            for (const Point &pi: inters) {
                // printf("intersection: (%.2f, %.2f, %.2f)\n", pi.x, pi.y, pi.z);
                if (is_point_in_triangle(pi, p1, p2, p3))
                    point_in = 1;
                else
                    point_out = 1;
            }
            if (point_in && point_out) printf("YES\n");
            else printf("NO\n");
        }
    }        
    return 0;
}
