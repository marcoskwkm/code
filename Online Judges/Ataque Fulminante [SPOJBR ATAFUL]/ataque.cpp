#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0);
const int NSTEP = 1000;

struct Point {
    double x,y;
    Point() {}
    Point(double angle) { x = cos(angle), y = sin(angle); }
    Point(double xx,double yy) { x = xx; y = yy; }
};

typedef Point Vector;
typedef vector<Point> Poly;

double norm(Point p) { return sqrt(p.x*p.x + p.y*p.y); }
Point operator*(double k, const Point &p) { return Point(k*p.x, k*p.y); }
Point operator/(const Point &p, double k) { return Point(p.x / k, p.y / k); }
Point operator+(const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y); }
Point operator-(const Point &a, const Point &b) { return Point(a.x-b.x, a.y-b.y); }
double operator*(const Point &a, const Point &b) { return a.x*b.x + a.y*b.y; }
double operator^(const Point &a, const Point &b) { return a.x*b.y - a.y*b.x; }

void normalize(double &angle) {
    while (angle > PI) angle -= 2 * PI;
    while (angle < -PI) angle += 2 * PI;
}

bool is_between(Vector v, Vector a, Vector b) {
    return ((a ^ v) >= 0 && (v ^ b) >= 0);
}

int classify(double angle, Vector va, Vector vb, Vector vc) {
    Vector v(cos(angle), sin(angle));
    if (is_between(v, va, vb)) return 1;
    if (is_between(v, vb, vc)) return 2;
    return 0;
}

pair<Point, Point> get_inters(double angle, Point C, double cr) {
    double l = 0, r = INF;
    for (int step = 0; step < NSTEP; step++) {
        double th = (r - l) / 3;
        double m1 = l + th, m2 = r - th;
        Point P1(m1 * cos(angle), m1 * sin(angle));
        Point P2(m2 * cos(angle), m2 * sin(angle));
        double d1 = norm(P1 - C), d2 = norm(P2 - C);
        if (d1 > d2) l = m1;
        else r = m2;
    }
    double center = l;
    
    l = 0, r = center;
    for (int step = 0; step < NSTEP; step++) {
        double mid = (l + r) / 2;
        Point P(mid * cos(angle), mid * sin(angle));
        double d = norm(P - C);
        if (d < cr) r = mid;
        else l = mid;
    }
    Point I1(l * cos(angle), l * sin(angle));
    
    l = center, r = INF;
    for (int step = 0; step < NSTEP; step++) {
        double mid = (l + r) / 2;
        Point P(mid * cos(angle), mid * sin(angle));
        double d = norm(P - C);
        if (d < cr) l = mid;
        else r = mid;
    }
    Point I2(l * cos(angle), l * sin(angle));

    return make_pair(I1, I2);
}

double get_area(Point A, Point B, Point C, double r) {
    Vector va = A - C, vb = B - C;
    double angle = acos((va * vb) / r / r);
    double area = PI * r * r * angle / (2 * PI);
    area -= fabs(va ^ vb) / 2;
    return area;
}

int main() {
    Point C, O;
    int r;
    while(scanf("%lf%lf%d", &C.x, &C.y, &r) && r) {
        double total = PI * r * r;
        double dir, theta;
        scanf("%lf%lf%lf%lf", &O.x, &O.y, &dir, &theta);
        dir = dir * PI / 180;
        theta = theta * PI / 180;
        C = C - O;
        dir -= atan2(C.y, C.x);
        C = Point(norm(C), 0);
        double r_angle = asin(r / C.x);
        Vector va(cos(-r_angle), sin(-r_angle));
        Vector vb(1, 0);
        Vector vc(cos(r_angle), sin(r_angle));        

        double lo_angle = dir - theta / 2;
        double hi_angle = dir + theta / 2;
        Vector vlo(lo_angle), vhi(hi_angle);
        // printf("dir = %.2f\n", dir);
        // printf("(%.2f, %.2f), (%.2f, %.2f)\n", va.x, va.y, vc.x, vc.y);
        // printf("(%.2f, %.2f), (%.2f, %.2f), (%.2f, %.2f)\n",
        //        vlo.x, vlo.y, vb.x, vb.y, vhi.x, vhi.y);

        if (classify(lo_angle, va, vb, vc) == 0) {
            if (classify(hi_angle, va, vb, vc) == 0) {
                // printf("%.2f %.2f\n", (vlo ^ vb), (vb ^ vhi));
                if (is_between(vb, vlo, vhi))
                    printf("%.1f\n", total);
                else
                    printf("0.0\n");
            }
            else {
                pair<Point, Point> inters = get_inters(hi_angle, C, r);
                double area = get_area(inters.first, inters.second, C, r);
                if (classify(hi_angle, va, vb, vc) == 2)
                    area = PI * r * r - area;
                printf("%.1f\n", area);
            }
        }
        else if (classify(lo_angle, va, vb, vc) == 1) {
            pair<Point, Point> ilo = get_inters(lo_angle, C, r);
            double area = PI * r * r - get_area(ilo.first, ilo.second, C, r);
            if (classify(hi_angle, va, vb, vc) == 0)
                printf("%.1f\n", area);
            else {
                pair<Point, Point> ihi = get_inters(hi_angle, C, r);
                if (classify(hi_angle, va, vb, vc) == 1)
                    area -= PI * r * r - get_area(ihi.first, ihi.second, C, r);
                else
                    area -= get_area(ihi.first, ihi.second, C, r);
                printf("%.1f\n", area);
            }
        }
        else {
            pair<Point, Point> ilo = get_inters(lo_angle, C, r);
            double area = get_area(ilo.first, ilo.second, C, r);
            if (classify(hi_angle, va, vb, vc) == 0) {
                printf("%.1f\n", area);
            }
            else {
                pair<Point, Point> ihi = get_inters(hi_angle, C, r);                
                if (classify(hi_angle, va, vb, vc) == 1)
                    area += get_area(ihi.first, ihi.second, C, r);
                else                    
                    area = area - get_area(ihi.first, ihi.second, C, r);
                printf("%.1f\n", area);
            }
        }
    }    
    return 0;
}
