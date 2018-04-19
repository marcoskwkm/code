// WA?

#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const long double SQRT2 = sqrt(2.L);
const long double PI = acos(-1.0L);
const long double EPS = 1e-9;
const long double LIM1 = PI / 4;
const long double LIM2 = atan(1 / SQRT2);
const int NREP = 200;

template<class T> struct Point {
    T x, y, z;
    Point(T _x = 0, T _y = 0, T _z = 0) : x(_x), y(_y), z(_z) {}
    Point<T> rotate_x(T alpha) {
        return Point<T>(x,
                        y * cos(alpha) - z * sin(alpha),
                        y * sin(alpha) + z * cos(alpha));
    }
    Point<T> rotate_y(T alpha) {
        return Point<T>(z * sin(alpha) + x * cos(alpha),
                        y,
                        z * cos(alpha) - x * sin(alpha));
    }
    long double norm2() { return x*x + y*y + z*z; }
};
template<class T> using Vector = Point<T>;
template<class T> using Poly = vector<Point<T>>;

template<class T> Point<T> operator-(const Point<T> &p) {
    return Point<T>(-p.x, -p.y, -p.z);
}
template<class T> Point<T> operator-(const Point<T> &p, const Point<T> &q) {
    return Point<T>(p.x - q.x, p.y - q.y, p.z - q.z);
}
template<class T> Point<T> operator+(const Point<T> &p, const Point<T> &q) {
    return Point<T>(p.x + q.x, p.y + q.y, p.z + q.z);
}
template<class T> T operator*(const Vector<T> &u, const Vector<T> &v) {
    return u.x * v.x + u.y * v.y;
}
template<class T> T operator^(const Vector<T> &u, const Vector<T> &v) {
    return u.x * v.y - u.y * v.x;
}

template<class T> Poly<T> convex_hull(Poly<T> poly) {
    sort(poly.begin(), poly.end(), [](const Point<T> &a, const Point<T> &b) {
        if (a.x == b.x) return a.y < b.y;
        return a.x < b.x;
    });
    Poly<T> top, bot;
    size_t top_s = 0, bot_s = 0;
    for (const Point<T> &p: poly) {
        while (top_s > 1 &&
               ((top[top_s - 2] - top[top_s - 1]) ^ (p - top[top_s - 1])) <= 0)
            top_s--, top.pop_back();
        while (bot_s > 1 &&
               ((p - bot[bot_s - 1])^(bot[bot_s - 2] - bot[bot_s - 1])) <= 0)
            bot_s--, bot.pop_back();
        top.push_back(p);
        bot.push_back(p);
        top_s++, bot_s++;
    }
    for (int i = (int)top_s - 2; i > 0; i--)
        bot.push_back(top[i]);
    return bot;
}

template<class T> long double get_area(Poly<T> poly) {
    long double ret = 0;
    int n = poly.size();
    for (int i = 0; i < n; i++) {
        int j = (i == n - 1 ? 0 : i + 1);
        ret += poly[i] ^ poly[j];
    }
    if (ret < 0) ret = -ret;
    return 0.5 * ret;
}

int main() {
    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        printf("Case #%d:\n", t);
        long double A;
        cin >> A;
        Vector<long double> v1(0.5, 0, 0), v2(0, 0.5, 0), v3(0, 0, 0.5);
        long double l = 0, r = LIM1;
        if (A > SQRT2 + EPS) {
            r = LIM2;
            v1 = v1.rotate_x(PI / 4);
            v2 = v2.rotate_x(PI / 4);
            v3 = v3.rotate_x(PI / 4);
        }
        // debug("v1 = %.2Lf %.2Lf %.2Lf\n", v1.x, v1.y, v1.z);
        // debug("v2 = %.2Lf %.2Lf %.2Lf\n", v2.x, v2.y, v2.z);
        // debug("v3 = %.2Lf %.2Lf %.2Lf\n", v3.x, v3.y, v3.z);
        for (int s = 0; s < NREP; s++) {
            long double m = (l + r) / 2;
            Vector<long double> vv1 = v1.rotate_y(m);
            Vector<long double> vv2 = v2.rotate_y(m);
            Vector<long double> vv3 = v3.rotate_y(m);
            Poly<long double> p;
            p.push_back(vv1 + vv2 + vv3);
            p.push_back(vv1 + vv2 - vv3);
            p.push_back(vv1 - vv2 + vv3);
            p.push_back(vv1 - vv2 - vv3);
            p.push_back(-vv1 + vv2 + vv3);
            p.push_back(-vv1 + vv2 - vv3);
            p.push_back(-vv1 - vv2 + vv3);
            p.push_back(-vv1 - vv2 - vv3);
            // debug("vv1 = %.2Lf %.2Lf %.2Lf\n", vv1.x, vv1.y, vv1.z);
            // debug("vv2 = %.2Lf %.2Lf %.2Lf\n", vv2.x, vv2.y, vv2.z);
            // debug("vv3 = %.2Lf %.2Lf %.2Lf\n", vv3.x, vv3.y, vv3.z);
            // for (auto pp: p) debug("%.12Lf %.12Lf %.12Lf\n", pp.x, pp.y, pp.z);
            long double area = get_area(convex_hull(p));
            // debug("m = %.6Lf, area = %.9Lf\n", m, area);
            if (area < A) l = m;
            else r = m;
        }
        // debug("l = %.9Lf\n", l);
        v1 = v1.rotate_y(l);
        v2 = v2.rotate_y(l);
        v3 = v3.rotate_y(l);
        // debug("%.12Lf %.12Lf %.12Lf\n", v1.norm2(), v2.norm2(), v3.norm2());
        printf("%.12Lf %.12Lf %.12Lf\n", v1.z, v1.x, v1.y);
        printf("%.12Lf %.12Lf %.12Lf\n", v2.z, v2.x, v2.y);
        printf("%.12Lf %.12Lf %.12Lf\n", v3.z, v3.x, v3.y);
    }        
    return 0;
}
