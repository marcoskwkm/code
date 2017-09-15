#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXD = 510;

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

// Returns convex hull in counterclockwise order.
template<class T> Poly<T> get_convex_hull(Poly<T> poly) {
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

char grid[MAXD][MAXD];

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        int n, m;
        scanf("%d%d", &n, &m);

        Poly<int> poly;
        int best = 0;
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                scanf(" %c", &grid[r][c]);
                if (grid[r][c] == '#') {
                    poly.push_back(Point<int>(r, c));
                    best++;
                }
            }
        }
        if (best == 0) {
            printf("0\n");
            continue;
        }
        poly = get_convex_hull(poly);
        // for (const auto &p: poly) printf("(%d, %d)\n", p.x, p.y);
        for (size_t i = 0; i < poly.size(); i++) {
            int j = (i + 1) % poly.size();
            int dr = poly[j].x - poly[i].x;
            int dc = poly[j].y - poly[i].y;
            if (dr == 0 && dc == 0) continue;
            int d = __gcd(abs(dr), abs(dc));
            dr /= d, dc /= d;
            for (int k = 1; k <= d; k++) {
                // printf("Test %d %d\n", k * dr, k * dc);
                int got = 0;
                for (int r = 0; r < n; r++) {
                    for (int c = 0; c < m; c++) {
                        int pr = r - k * dr, pc = c - k * dc;
                        if (0 <= pr && pr < n && 0 <= pc && pc < m) continue;
                        int cnt = 0;
                        int nr = r, nc = c;
                        while (0 <= nr && nr < n && 0 <= nc && nc < m) {
                            if (grid[nr][nc] == '#') cnt++;
                            else {
                                if (cnt == 1) {
                                    got = INF;
                                    goto loopend;
                                }
                                else got += (cnt + 1) / 2;
                                cnt = 0;
                            }
                            nr += k * dr, nc += k * dc;
                        }
                        if (cnt == 1) {
                            got = INF;
                            goto loopend;
                        }
                        got += (cnt + 1) / 2;
                    }
                }
            loopend:
                // printf("got = %d\n", got);
                best = min(best, got);
            }                
        }
        cout << best << endl;
    }        
    return 0;
}
