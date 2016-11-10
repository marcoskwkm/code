#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 110;

struct Rectangle {
    int x0, y0, x1, y1;
    Rectangle (int x = 0, int y = 0, int xx = 0, int yy = 0) {
        x0 = x, y0 = y, x1 = xx, y1 = yy;
    }
};

Rectangle rect[MAXN];
long double dist[MAXN];
bool done[MAXN];
int n, l, u;

long double dist2(long double x0, long double y0, long double x1, long double y1) {
    return sqrt((x0 - x1)*(x0 - x1) + (y0 - y1)*(y0 - y1));
}

long double get_dist(int i, int j) {
    if (!(rect[i].x1 < rect[j].x0 || rect[j].x1 < rect[i].x0))
        return max(0, max(rect[i].y0, rect[j].y0) - min(rect[i].y1, rect[j].y1));
    if (!(rect[i].y1 < rect[j].y0 || rect[j].y1 < rect[i].y0))
        return max(0, max(rect[i].x0, rect[j].x0) - min(rect[i].x1, rect[j].x1));
    long double ret = LINF;
    ret = min(ret, dist2(rect[i].x0, rect[i].y0, rect[j].x0, rect[j].y0));
    ret = min(ret, dist2(rect[i].x0, rect[i].y0, rect[j].x0, rect[j].y1));
    ret = min(ret, dist2(rect[i].x0, rect[i].y0, rect[j].x1, rect[j].y0));
    ret = min(ret, dist2(rect[i].x0, rect[i].y0, rect[j].x1, rect[j].y1));
    ret = min(ret, dist2(rect[i].x0, rect[i].y1, rect[j].x0, rect[j].y0));
    ret = min(ret, dist2(rect[i].x0, rect[i].y1, rect[j].x0, rect[j].y1));
    ret = min(ret, dist2(rect[i].x0, rect[i].y1, rect[j].x1, rect[j].y0));
    ret = min(ret, dist2(rect[i].x0, rect[i].y1, rect[j].x1, rect[j].y1));
    ret = min(ret, dist2(rect[i].x1, rect[i].y0, rect[j].x0, rect[j].y0));
    ret = min(ret, dist2(rect[i].x1, rect[i].y0, rect[j].x0, rect[j].y1));
    ret = min(ret, dist2(rect[i].x1, rect[i].y0, rect[j].x1, rect[j].y0));
    ret = min(ret, dist2(rect[i].x1, rect[i].y0, rect[j].x1, rect[j].y1));
    ret = min(ret, dist2(rect[i].x1, rect[i].y1, rect[j].x0, rect[j].y0));
    ret = min(ret, dist2(rect[i].x1, rect[i].y1, rect[j].x0, rect[j].y1));
    ret = min(ret, dist2(rect[i].x1, rect[i].y1, rect[j].x1, rect[j].y0));
    ret = min(ret, dist2(rect[i].x1, rect[i].y1, rect[j].x1, rect[j].y1));
    return ret;
}        

void dijkstra(int s) {
    for (int i = 0; i <= n; i++)
        dist[i] = LINF;
    memset(done, 0, sizeof(done));
    dist[s] = 0;
    while (1) {
        long double d = LINF;
        int v = -1;
        for (int i = 0; i <= n; i++) {
            if (dist[i] < d && !done[i]) {
                d = dist[i];
                v = i;
            }
        }
        if (v == -1) break;
        done[v] = 1;
        for (int i = 0; i <= n; i++) {
            if (done[i]) continue;
            dist[i] = min(dist[i], d + get_dist(v, i));
        }
    }
}            

int main() {
    #ifndef HOME
    freopen("street.in", "r", stdin);
    #endif

    int t;
    for (scanf("%d", &t); t--;) {
        scanf("%d%d%d", &n, &l, &u);
        for (int i = 0; i < n; i++) {
            int h, w, d, k;
            scanf("%d%d%d%d", &h, &w, &d, &k);
            if (k == 0) rect[i].x0 = 0, rect[i].x1 = w;
            else rect[i].x0 = u - w, rect[i].x1 = u;
            rect[i].y0 = d, rect[i].y1 = d + h;
        }
        long double ans = l;
        rect[n] = Rectangle(0, 0, u, 0);
        dijkstra(n);
        for (int i = 0; i < n; i++) {
            ans = min(ans, dist[i] + max(0, l - rect[i].y1));
            // printf("dist[%d] = %.2Lf\n", i, dist[i]);
        }
        cout << fixed << setprecision(6) << ans << endl;
    }    
    return 0;
}
