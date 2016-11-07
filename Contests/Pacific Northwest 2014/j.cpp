#include <bits/stdc++.h>
using namespace std;

typedef long long lint;
typedef pair<int ,int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const int MAXD = 310;
const int MAXN = MAXD * MAXD;

typedef int CTYPE;

struct Point {
    CTYPE x,y;
    Point() {}
    Point(CTYPE xx,CTYPE yy) { x = xx; y = yy; }
};

typedef Point Vector;
typedef vector<Point> Poly;

double norm(Vector &v) { return sqrt(v.x * v.x + v.y * v.y); }
Vector operator*(double k, const Vector &v) { return Vector(k * v.x, k * v.y); }
Vector operator/(const Vector &v, double k) { return Vector(v.x / k, v.y / k); }
Point operator+(const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y); }
Point operator-(const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
CTYPE operator*(const Vector &u, const Vector &v) { return u.x * v.x + u.y * v.y; }
CTYPE operator^(const Vector &u, const Vector &v) { return u.x * v.y - u.y * v.x; }

char grid[MAXD][MAXD];

// Returns convex hull in clockwise-order.
Poly convex_hull(vector<Point> poly) {
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

int h, w;
bool mark[MAXD][MAXD];

int test(int dr, int dc) {
    memset(mark, 0, sizeof(mark));
    int ret = 0;
    for (int r = 0; r < h; r++) {
        int nr = r + dr;
        if (nr < 0 || nr >= h) continue;
        for (int c = 0; c < w; c++) {
            int nc = c + dc;
            if (nc < 0 || nc >= w) continue;
            mark[r][c] = mark[nr][nc] = 1;
            if (grid[r][c] == '#' && grid[nr][nc] == '.') {
                printf("(%d, %d) -/> (%d, %d)\n", r, c, nr, nc);
                return INF;
            }
            ret += (grid[r][c] == '#');
        }        
    }
    for (int r = 0; r < h; r++)
        for (int c = 0; c < w; c++)
            if (!mark[r][c] && grid[r][c] != '.') {
                printf("failed here! (%d, %d)\n", r, c);
                return INF;
            }
    return ret;
}

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        scanf("%d%d", &h, &w);
        Poly p;
        for (int r = 0; r < h; r++) {
            for (int c = 0; c < w; c++) {
                scanf(" %c", &grid[r][c]);
                if (grid[r][c] == '#')
                    p.push_back(Point(r, c));
            }
        }
        Poly hull = convex_hull(p);
        int ans = test(0, 0);
        printf("%d\n", test(0, 3));
        return 0;
        for (int i = 0; i < (int)hull.size(); i++) {
            int j = (i + 1) % hull.size();
            Vector v = p[j] - p[i];
            if (v.x == 0 && v.y == 0) continue;
            int d = __gcd(abs(v.x), abs(v.y));
            int dx = v.x / d, dy = v.y / d;
            for (int k = 1; k <= d; k++)
                ans = min(ans, test(dx * j, dy * j));
        }
        printf("%d\n", ans);
    }                
    return 0;
}
   
