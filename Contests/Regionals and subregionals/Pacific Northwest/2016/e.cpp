#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0);
const double EPS = 1e-9;

struct Point {
    lint x, y;
    Point() {}
    Point(lint _x, lint _y) : x(_x), y(_y) {}
};

typedef Point Vector;
typedef vector<Point> Poly;

Point operator+(const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y); }
Point operator-(const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
lint operator*(const Vector &u, const Vector &v) { return u.x * v.x + u.y * v.y; }
lint operator^(const Vector &u, const Vector &v) { return u.x * v.y - u.y * v.x; }

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

lint area(vector<Point>& polygon) {
    double ret = 0;
    int n = polygon.size();
    for(int i=0;i<n;++i) {
        int j = (i == n-1 ?  0 : i+1);
        ret += polygon[i] ^ polygon[j];
    }
    return ret;
}

bool in_hull(const Point &p, const Poly &poly) {
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

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    Poly hull;
    for (int i = 0; i < k; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        hull.push_back(Point(x, y));
    }
    hull = convex_hull(hull);
    reverse(hull.begin(), hull.end()); // ccw
    lint s = area(hull);

    vector<Point> rem;
    for (int i = k; i < n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        rem.push_back(Point(x, y));
    }

    Vector base = hull[1] - hull[0];
    sort(rem.begin(), rem.end(), [&](Point a, Point b) {
        Vector va = a - hull[0], vb = b - hull[0];
        double angle_a = atan2(base ^ va, base * va);
        double angle_b = atan2(base ^ vb, base * vb);
        if (angle_a < 0) angle_a += 2 * PI;
        if (angle_b < 0) angle_b += 2 * PI;
        return angle_a < angle_b;
    });

    int hs = hull.size();
    int l = 1, nxt_l = 2, prev_l = 0, r = 2, nxt_r = 3 % hs;
    lint ans = s;
    lint cur_area = 0;
    // debug("Hull:\n");
    // for (Point &p: hull) debug("(%lld, %lld)\n", p.x, p.y);
    // debug("\nRemaining:\n");
    // for (Point &p: rem) debug("(%lld, %lld)\n", p.x, p.y);    
    for (const Point &p: rem) {
        if (in_hull(p, hull)) continue;        
        while (((hull[l] - hull[prev_l]) ^ (p - hull[prev_l])) < 0 ||
               ((hull[nxt_l] - hull[l]) ^ (p - hull[l])) > 0) {
            cur_area -= ((hull[nxt_l] - hull[l]) ^ (hull[r] - hull[l]));
            prev_l = l;
            l = nxt_l;
            nxt_l = (nxt_l + 1) % hs;
            if (r == l) {
                r = nxt_r;
                nxt_r = (nxt_r + 1) % hs;
            }
        }
        while (((hull[r] - hull[nxt_r]) ^ (p - hull[nxt_r])) > 0) {
            cur_area += ((hull[r] - hull[l]) ^ (hull[nxt_r] - hull[l]));
            r = nxt_r;
            nxt_r = (nxt_r + 1) % hs;
        }
        ans = max(ans, s - cur_area + ((p - hull[r]) ^ (p - hull[l])));
    }

    printf("%lld.%lld\n", ans / 2, 5 * (ans & 1));

    return 0;
}
