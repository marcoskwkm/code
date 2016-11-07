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
int dpv[MAXD];

int dp[MAXD][2];

int solve(int len) {
    dp[0][0] = 0;
    dp[0][1] = INF;
    for (int i = 0; i < len; i++) {
        if (dpv[i] == 1) {
            dp[i + 1][1] = 1 + min(dp[i][0], dp[i][1]);
            dp[i + 1][0] = dp[i][1];
        }
        else {
            dp[i + 1][1] = INF;
            dp[i + 1][0] = dp[i][0];
        }
    }
    return dp[len][0];
}    

int test(int dr, int dc) {
    if (dr < 0) {
        dr = -dr;
        dc = -dc;
    }
    else if (dr == 0 && dc < 0) dc = -dc;
    
    memset(mark, 0, sizeof(mark));
    int ret = 0;
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            if (mark[r][c]) continue;
            int cr = r, cc = c;
            int len = 0;
            while (0 <= cr && cr < h && 0 <= cc && cc < w) {
                mark[cr][cc] = 1;
                dpv[len++] = (grid[cr][cc] == '#');
                cr += dr, cc += dc;
            }
            int got = min(INF, solve(len));
            if (got == INF) return INF;
            ret += got;
        }
    }

    return ret;
}

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        scanf("%d%d", &h, &w);
        Poly p;
        int qx = 0;
        for (int r = 0; r < h; r++) {
            for (int c = 0; c < w; c++) {
                scanf(" %c", &grid[r][c]);
                if (grid[r][c] == '#') {
                    p.push_back(Point(r, c));
                    qx++;
                }
            }
        }
        Poly hull = convex_hull(p);
        int ans = qx;
        for (int i = 0; i < (int)hull.size(); i++) {
            int j = (i + 1) % hull.size();
            Vector v = hull[j] - hull[i];
            if (v.x == 0 && v.y == 0) continue;
            int d = __gcd(abs(v.x), abs(v.y));
            int dx = v.x / d, dy = v.y / d;
            for (int k = 1; k <= d; k++)
                ans = min(ans, test(dx * k, dy * k));
        }
        printf("%d\n", ans);
    }                
    return 0;
}
   
