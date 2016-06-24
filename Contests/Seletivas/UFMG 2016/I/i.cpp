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

//( cmp(a,b) _ 0 ) means (a _ b)
inline int cmp(double a, double b = 0) { return (a < b + EPS) ? (a + EPS < b) ? -1 : 0 : 1; }

struct Point {
    CTYPE x,y;
    Point(){}
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

double norm(Point &p) { return sqrt(p.x*p.x + p.y*p.y); }
Point operator*(double k, const Point &p) { return Point(k*p.x, k*p.y); }
Point operator+(const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y); }
Point operator-(const Point &a, const Point &b) { return Point(a.x-b.x, a.y-b.y); }
CTYPE operator*(const Point &a, const Point &b) { return a.x*b.x + a.y*b.y; }
CTYPE operator^(const Point &a, const Point &b) { return a.x*b.y - a.y*b.x; }
Point operator/(const Point &a, double k) { return Point(a.x / k, a.y / k); }
Point operator*(const Point &a, double k) { return Point(a.x * k, a.y * k); }

int main() {
    Point A, B, S;    
    scanf("%lf%lf", &A.x, &A.y);
    scanf("%lf%lf", &B.x, &B.y);
    scanf("%lf%lf", &S.x, &S.y);
    if (A.x == B.x && A.y == B.y) {
        printf("%.2f %.2f\n", S.x, S.y);
        return 0;
    }
    Point M = (A + B) / 2;
    Vector dir = Vector(A.y - B.y, B.x - A.x);
    dir = dir / norm(dir);
    Vector v = S - M;
    double dist = (v * dir);
    Point P = M + dir * dist;
    printf("%.2f %.2f\n", P.x, P.y);    
    return 0;
}
