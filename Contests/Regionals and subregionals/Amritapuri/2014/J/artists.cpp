#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 110;
const double PI = acos(-1.0);
const double EPS = 1e-12;

template<class T> struct Point {
    T x, y;
    Point(T _x = 0, T _y = 0) : x(_x), y(_y) {}
    T norm2() { return x * x + y * y; }
    T norm() { return sqrt(norm2()); }
    Point<T> rotate(T alpha) {
        return Point<T>(x * cos(alpha) - y * sin(alpha),
                        x * sin(alpha) + y * cos(alpha));
    }
    T arg() { return atan2(y, x); } // [-PI, PI]
};
template<class T> using Vector = Point<T>;

template<class T> Point<T> operator-(const Point<T> &p, const Point<T> &q) {
    return Point<T>(p.x - q.x, p.y - q.y);
}
template<class T> Point<T> operator+(const Point<T> &p, const Point<T> &q) {
    return Point<T>(p.x + q.x, p.y + q.y);
}
template<class T> T operator*(const Vector<T> &u, const Vector<T> &v) {
    return u.x * v.x + u.y * v.y;
}
template<class T> T operator^(const Vector<T> &u, const Vector<T> &v) {
    return u.x * v.y - u.y * v.x;
}
template<class T> Vector<T> operator*(T k, const Vector<T> &v) {
    return Vector<T>(v.x * k, v.y * k);
}
template<class T> Vector<T> operator*(const Vector<T> &v, T k) {
    return k * v;
}
template<class T> Vector<T> operator/(const Vector<T> &v, T k) {
    return Vector<T>(v.x / k, v.y / k);
}

template<class T> struct Circle {
    Point<T> o;
    T r;
    Circle(T _x = 0, T _y = 0, T _r = 0) : o(_x, _y), r(_r) {}
    Circle(Point<T> _o, T _r) : o(_o), r(_r) {}    
};

// Assumes there are two intersection points
// Intersection arc goes from first point to second counter-clockwise
template<class T> pair<Point<T>, Point<T>> get_intersection(
    const Circle<T> &c1, const Circle<T> &c2) {
    Vector<T> vd = c2.o - c1.o;
    T d = vd.norm();
    T alpha = acos((c1.r * c1.r + d * d - c2.r * c2.r) / (2 * c1.r * d));
    Vector<T> vr = vd / d * c1.r;
    return make_pair(c1.o + vr.rotate(-alpha), c1.o + vr.rotate(+alpha));
}

Circle<double> c[MAXN];

int main() {
    int t;
    for (cin >> t; t--;) {
        int n;
        cin >> n;        
        for (int i = 0; i < n; i++) {
            int x, y, r;
            cin >> x >> y >> r;
            c[i] = Circle<double>(x, y, r);
        }

        double ans = 0;
        for (int i = 0; i < n; i++) {
            vector<pair<double, double>> covered;
            for (int j = i + 1; j < n; j++) {
                double dist = (c[j].o - c[i].o).norm();
                if (dist <= c[j].r - c[i].r + EPS) {
                    covered.push_back(make_pair(-PI, PI));
                    continue;
                }
                if (dist <= c[i].r - c[j].r + EPS) continue;                    
                if (dist + EPS >= c[i].r + c[j].r) continue;
                Point<double> P, Q;
                tie(P, Q) = get_intersection(c[i], c[j]);
                // printf("Inter %d x %d: (%.2f, %.2f) and (%.2f, %.2f)\n",
                //        i, j, P.x, P.y, Q.x, Q.y);
                double arg_P  = (P - c[i].o).arg(), arg_Q = (Q - c[i].o).arg();
                // printf("Inter %d x %d: add [%.2f, %.2f]\n", i, j, arg_P, arg_Q);
                if (arg_Q < arg_P) {
                    // printf("Inter %d x %d: push [%.2f, %.2f]\n", i, j, arg_P, PI);
                    // printf("Inter %d x %d: push [%.2f, %.2f]\n", i, j, -PI, arg_Q);
                    covered.push_back(make_pair(arg_P, PI));
                    covered.push_back(make_pair(-PI, arg_Q));
                }
                else {
                    // printf("Inter %d x %d: push [%.2f, %.2f]\n", i, j, arg_P, arg_Q);
                    covered.push_back(make_pair(arg_P, arg_Q));
                }
            }
                
            sort(covered.begin(), covered.end());
            double uncovered = 2 * PI * c[i].r;
            double cur_l = -PI, cur_r = -PI;
            for (auto interval: covered) {
                // printf("i = %d: now looking at [%.2f, %.2f]\n", i, interval.first, interval.second)
                    ;
                if (cur_r < interval.first) {
                    uncovered -= (cur_r - cur_l) * c[i].r;
                    // printf("i = %d: uncovered [%.2f, %.2f]\n", i, cur_l, cur_r);
                    cur_l = interval.first;
                }
                cur_r = max(cur_r, interval.second);
            }
            // printf("i = %d: uncovered [%.2f, %.2f]\n", i, cur_l, cur_r);
            uncovered -= (cur_r - cur_l) * c[i].r;
            // printf("i = %d: uncovered = %.6f\n", i, uncovered);
            ans += uncovered;
        }
        printf("%.12f\n", ans);        
    }
    return 0;
}
