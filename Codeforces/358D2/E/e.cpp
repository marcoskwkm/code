#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 5010;

struct Point {
    lint x,y;
    Point(){}
    Point(lint xx,lint yy) { x = xx; y = yy; }
};

typedef Point Vector;
typedef vector<Point> Poly;

Point operator+(const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y); }
Point operator-(const Point &a, const Point &b) { return Point(a.x-b.x, a.y-b.y); }
lint operator*(const Point &a, const Point &b) { return a.x*b.x + a.y*b.y; }
lint operator^(const Point &a, const Point &b) { return a.x*b.y - a.y*b.x; }

Poly convexHull(vector<Point> poly) {
    sort(poly.begin(), poly.end(), [](const Point &a, const Point &b) {
        if (a.x == b.x) return a.y < b.y;
        return a.x < b.x;
    });
    Poly top, bot;
    int tlen = 0, blen = 0;
    for (const Point &p: poly) {
        while (tlen > 1 && ((top[tlen - 2] - top[tlen - 1])^(p - top[tlen - 1])) <= 0) {
            tlen--;
            top.pop_back();
        }
        while (blen > 1 && ((p - bot[blen - 1])^(bot[blen - 2] - bot[blen - 1])) <= 0) {
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

int main() {
    int n;
    lint s;
    cin >> n >> s;
    vector<Point> vp;
    for (int i = 0; i < n; i++) {
        Point p;
        cin >> p.x >> p.y;
        vp.push_back(p);
    }
    Poly hull = convexHull(vp);
            
    lint max_area = 0;
    n = hull.size();
    Point p1, p2, p3;
    for (int i = 0; i < n; i++) {
        int r = (i + 1) % n;
        for (int l = r; l != i; l = (l + 1) % n) {
            
            Vector iu = hull[r] - hull[i];
            Vector iv = hull[l] - hull[i];
            lint cur_area = (iu ^ iv);
            while ((r + 1) % n != i) {
                Vector u = hull[(r + 1) % n] - hull[i];
                Vector v = hull[l] - hull[i];
                if ((u ^ v) > cur_area) {
                    cur_area = (u ^ v);
                    r = (r + 1) % n;
                }
                else break;
            }
            if (cur_area > max_area) {
                max_area = cur_area;
                p1 = hull[i]; p2 = hull[l]; p3 = hull[r];
            }
            if (l == r) r = (r + 1) % n;
        }
    }
    assert(max_area > 0);
    // printf("triangle:\n");
    // printf("%lld, %lld\n %lld, %lld\n %lld, %lld\n",
    //        p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
    Point pa(p1.x - p2.x + p3.x, p1.y - p2.y + p3.y);
    Point pb(2*p1.x - pa.x, 2*p1.y - pa.y);
    Point pc(2*p2.x - pb.x, 2*p2.y - pb.y);
    cout << pa.x << " " << pa.y << endl;
    cout << pb.x << " " << pb.y << endl;
    cout << pc.x << " " << pc.y << endl;
    return 0;
}
