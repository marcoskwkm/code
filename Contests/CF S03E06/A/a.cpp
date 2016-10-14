#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const double EPS = 1e-9;
const double PI = acos(-1.0);

int cmp(double a, double b = 0) { return (a < b + EPS) ? (a + EPS < b) ? -1 : 0 : 1; }

struct Point {
    double x, y;
    Point() {}
    Point(double xx, double yy) { x = xx; y = yy; }
};

typedef Point Vector;
typedef vector<Point> Poly;

double norm(const Vector &v) { return sqrt(v.x*v.x + v.y*v.y); }
double operator*(const Vector &u, const Vector &v) { return u.x*v.x + u.y*v.y; }
double operator^(const Vector &u, const Vector &v) { return u.x*v.y - u.y*v.x; }
Point operator-(const Point &p, const Point &q) { return Point(p.x - q.x, p.y - q.y); }
Point operator+(const Point &p, const Vector &v) { return Point(p.x + v.x, p.y + v.y); }
Vector operator*(const Vector &v, const double k) { return Vector(v.x * k, v.y * k); }
Vector operator/(const Vector &v, const double k) { return Vector(v.x / k, v.y / k); }

double get_area(double a, double b, double c) {
    double p = (a + b + c) / 2;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

double get_angle(double a, double b, double c) {
    double Sabc = get_area(a, b, c);
    double Rabc = a * b * c / 4 / Sabc;
    double sin_beta = c / 2 / Rabc;
    double cos_beta = (a*a + b*b - c*c) / (2 * a * b);
    return atan2(sin_beta, cos_beta);
}

pair<Point, Point> get_parallel_line(Point P, Vector v, double w) {
    Vector orth(v.y, -v.x);
    orth = orth / norm(v) * w;
    Point pivot_a = P + orth;
    Point pivot_b = pivot_a + v;
    return make_pair(pivot_a, pivot_b);
}

Point get_intersection(const Point &p, const Point &q, const Point &r, const Point &s) {
    Point a = q - p, b = s - r, c = Point(p ^ q, r ^ s);
    return Point(Point(a.x, b.x) ^ c, Point(a.y, b.y) ^ c) / (a ^ b);
}

double solve(Poly &poly, double w) {
    int n = poly.size();
    Poly big_poly;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        int k = (j + 1) % n;
        Vector v = poly[j] - poly[i];
        Point V1, V2;
        tie(V1, V2) = get_parallel_line(poly[i], v, w);
        Vector u = poly[k] - poly[j];
        Point U1, U2;
        tie(U1, U2) = get_parallel_line(poly[j], u, w);
        big_poly.push_back(get_intersection(V1, V2, U1, U2));
    }

    double ans = 0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        ans += norm(big_poly[j] - big_poly[i]);
    }

    return ans;
}        

void solve_triangle(double a, double b, double c, double w) {
    Point A(0, 0), B(a, 0);
    double beta = get_angle(a, b, c);
    Vector BC(-b * cos(-beta), -b * sin(-beta));
    Point C = B + BC;
    Poly poly;
    poly.push_back(A); poly.push_back(B); poly.push_back(C);
    printf("%.3f\n", solve(poly, w));
}

int main() {
    double w;
    scanf("%lf", &w);
    double a, b, c, d, diag;
    scanf("%lf%lf%lf%lf%lf", &a, &b, &c, &d, &diag);
    Point A(0, 0);
    Point B(a, 0);
    if (cmp(a + b, diag) == 0) {
        // a + b, c, d forma triangulo
        solve_triangle(a + b, c, d, w);
        return 0;
    }

    if (cmp(c + d, diag) == 0) {
        // a, b, c + d forma triangulo
        solve_triangle(a, b, c + d, w);
        return 0;
    }

    double beta = get_angle(a, b, diag);
    Vector BC(-b * cos(-beta), -b * sin(-beta));
    Point C = B + BC;
    
    double alpha = get_angle(d, diag, c);
    Vector AD = (C - A) / norm(C - A) * d;
    AD = Vector(AD.x * cos(alpha) - AD.y * sin(alpha),
                AD.x * sin(alpha) + AD.y * cos(alpha));
    Point D = A + AD;

    if (cmp(a + d, norm(D - B)) == 0) {
        // b, c, a + d forma triangulo
        solve_triangle(b, c, a + d, w);
        return 0;
    }

    if (cmp(b + c, norm(D - B)) == 0) {
        // a, b + c, d forma triangulo
        solve_triangle(a, b + c, d, w);
        return 0;
    }

    Poly poly;
    poly.push_back(A); poly.push_back(B);
    poly.push_back(C); poly.push_back(D);

    printf("%.3f\n", solve(poly, w));

    /*
    printf("A = (%.2f, %.2f)\n", A.x, A.y);
    printf("B = (%.2f, %.2f)\n", B.x, B.y);
    printf("C = (%.2f, %.2f)\n", C.x, C.y);
    printf("D = (%.2f, %.2f)\n", D.x, D.y);
    printf("AB = %.2f\n", norm(B - A));
    printf("BC = %.2f\n", norm(C - B));
    printf("CD = %.2f\n", norm(D - C));
    printf("AD = %.2f\n", norm(D - A));
    printf("AC = %.2f\n", norm(C - A));
    printf("BD = %.2f\n", norm(D - B));
    */
    return 0;
}
