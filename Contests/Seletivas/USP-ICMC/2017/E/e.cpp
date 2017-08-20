#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;

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
template<class T> using Poly = vector<Point<T>>;

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

// Checks whether given point is inside a convex polygon.
// Assumes polygon vertices are given in CCW order.
template<class T> bool in_polygon(const Point<T> &p, const Poly<T> &poly) {
    Vector<T> vp = p - poly[0];
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

int main() {
    int n, m;
    cin >> n >> m;
    Poly<lint> p1, p2;
    for (int i = 0; i < n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        p1.push_back(Point<lint>(x, y));
    }
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        p2.push_back(Point<lint>(x, y));
    }

    reverse(p1.begin(), p1.end());
    reverse(p2.begin(), p2.end());

    bool ans = 1;
    for (const auto &p: p2) {
        if (!in_polygon(p, p1)) {
            ans = 0;
            break;
        }
    }
    if (ans) {
        printf("YES\n");
        return 0;
    }

    ans = 1;
    for (const auto &p: p1) {
        if (!in_polygon(p, p2)) {
            ans = 0;
            break;
        }
    }
    printf("%s\n", ans ? "YES" : "NO");
    return 0;
}
