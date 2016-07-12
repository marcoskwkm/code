#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)5e4 + 10;

typedef int CTYPE;

struct Point {
    int x, y;
    Point() {}
    Point(int a, int b) { x = a, y = b; }
    void read() { scanf("%d%d", &x, &y); x *= 2, y *= 2; }
} tree[MAXN];

typedef Point Vector;

Point operator+(const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y); }
Point operator-(const Point &a, const Point &b) { return Point(a.x-b.x, a.y-b.y); }
CTYPE operator*(const Point &a, const Point &b) { return a.x*b.x + a.y*b.y; }
CTYPE operator^(const Point &a, const Point &b) { return a.x*b.y - a.y*b.x; }

bool in[MAXN];

int main() {
    int n, h, w;
    while (scanf("%d%d%d", &n, &w, &h) && n) {
        int cnt = 0;
        Point center(w, h);
        for (int i = 0; i < n; i++)
            tree[i].read();

        sort(tree, tree + n, [&](Point a, Point b) {
            Vector va = a - center, vb = b - center;
            if (va.y < 0 || (va.y == 0 && va.x < 0)) va.y *= -1, va.x *= -1;
            if (vb.y < 0 || (vb.y == 0 && vb.x < 0)) vb.y *= -1, vb.x *= -1;
            return (va ^ vb) > 0;
        });

        for (int i = 0; i < n; i++) {
            if (tree[i].y < center.y || (tree[i].y == center.y && tree[i].x < center.x)) {
                cnt++;
                in[i] = 1;
            }
            else in[i] = 0;
        }

        int at = 0;
        while (2*cnt != n) {
            if (in[at]) cnt--;
            else cnt++;
            in[at] = !in[at];
            at = (at + 1) % n;
        }

        for (int i = 0; i < n; i++)
            if (in[i])
                printf("%d %d\n", tree[i].x / 2, tree[i].y / 2);
        
    }
    return 0;
}
