#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 1010;

struct Point {
    lint x, y;
    Point() {}
    Point(lint xx, lint yy) { x = xx; y = yy; }
};

typedef Point Vector;

Point operator-(const Point &a, const Point &b) { return Point(a.x-b.x, a.y-b.y); }
lint operator*(const Point &a, const Point &b) { return a.x*b.x + a.y*b.y; }
lint operator^(const Point &a, const Point &b) { return a.x*b.y - a.y*b.x; }

bool intersects(Point p, Point q, Point r, Point s) {
    Vector pq = q - p, rs = s - r;
    Vector pr = r - p, ps = s - p;
    Vector rp = p - r, rq = q - r;
    Vector qr = r - q, qs = s - q;
    if ((pq ^ pr) * (pq ^ ps) > 0) return 0;
    if ((rs ^ rp) * (rs ^ rq) > 0) return 0;
    if ((pq ^ rs) == 0) return (pr * ps <= 0 || qr * qs <= 0);        
    return 1;
}

vector<int> adj[MAXN];
int cmp[MAXN];
Point p[MAXN][2];

void dfs(int v, int c) {
    cmp[v] = c;
    for (int nxt: adj[v])
        if (cmp[nxt] == -1)
            dfs(nxt, c);
}

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) {
            adj[i].clear();
            cmp[i] = -1;
            scanf("%lld%lld%lld%lld", &p[i][0].x, &p[i][0].y, &p[i][1].x, &p[i][1].y);
        }
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                if (intersects(p[i][0], p[i][1], p[j][0], p[j][1])) {
                        adj[i].push_back(j);
                        adj[j].push_back(i);
                }
            }
        }
        int ncmp = 0;
        for (int v = 1; v <= n; v++)
            if (cmp[v] == -1)
                dfs(v, ncmp++);
        for (int q = 0; q < m; q++) {
            int x, y;
            scanf("%d%d", &x, &y);
            printf("%s\n", cmp[x] == cmp[y] ? "YES" : "NO");
        }
    }
    return 0;
}
