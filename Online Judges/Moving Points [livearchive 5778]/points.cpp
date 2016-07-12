#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef complex<long double> Complex;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 18;
const double EPS = 1e-9;
const double PI = acos(-1.0);

typedef double CTYPE;

//( cmp(a,b) _ 0 ) means (a _ b)
inline int cmp(double a, double b = 0) { return (a < b + EPS) ? (a + EPS < b) ? -1 : 0 : 1; }

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

double norm(Point &p) { return sqrt(p.x*p.x + p.y*p.y); }
Point operator*(double k, const Point &p) { return Point(k*p.x, k*p.y); }
Point operator+(const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y); }
Point operator-(const Point &a, const Point &b) { return Point(a.x-b.x, a.y-b.y); }
CTYPE operator*(const Point &a, const Point &b) { return a.x*b.x + a.y*b.y; }
CTYPE operator^(const Point &a, const Point &b) { return a.x*b.y - a.y*b.x; }

bool foi[1 << MAXN][MAXN];
double best_t[1 << MAXN][MAXN];
double best_x[1 << MAXN][MAXN], best_y[1 << MAXN][MAXN];
Point p[MAXN];
Vector v[MAXN];
int n, c;        
    
int main() {
    while (scanf("%d%d", &n, &c) && n) {
        for (int i = 0; i < n; i++) {
            double d, mod;
            scanf("%lf%lf%lf%lf", &p[i].x, &p[i].y, &d, &mod);
            d = d / 180. * PI;
            v[i] = Point(mod * cos(d), mod * sin(d));
        }
        memset(foi, 0, sizeof(foi));
        queue<pii> fila;
        best_t[0][n] = 0;
        best_x[0][n] = best_y[0][n] = 0;
        foi[0][n] = 1;
        fila.push(pii(0, n));
        double ans = LINF;
        while (!fila.empty()) {
            int mask, last;
            tie(mask, last) = fila.front();
            fila.pop();
            if (mask == (1 << n) - 1) ans = min(ans, best_t[mask][last]);
            double x = best_x[mask][last], y = best_y[mask][last];
            double cur_t = best_t[mask][last];
            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) continue;
                double px = p[i].x + cur_t*v[i].x, py = p[i].y + cur_t*v[i].y;
                double A = v[i].x*v[i].x + v[i].y*v[i].y - c*c;
                double B = 2*((px - x)*v[i].x + (py - y)*v[i].y);
                double C = (px - x)*(px - x) + (py - y)*(py - y);
                if (A < 0) {
                    A *= -1;
                    B *= -1;
                    C *= -1;
                }
                double t = (-B + sqrt(B*B - 4*A*C)) / (2 * A);
                if (best_t[mask | (1 << i)][i] > t + cur_t || !foi[mask | (1 << i)][i]) {
                    best_t[mask | (1 << i)][i] = t + cur_t;
                    best_x[mask | (1 << i)][i] = px + t*v[i].x;
                    best_y[mask | (1 << i)][i] = py + t*v[i].y;
                    if (!foi[mask | (1 << i)][i]) {
                        foi[mask | (1 << i)][i] = 1;
                        fila.push(pii(mask | (1 << i), i));
                    }
                }
            }
        }
        printf("%.2f\n", ans);        
    }
    return 0;
}
