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
    Point (lint xx, lint yy) { x = xx; y = yy; }
};

typedef Point Vector;

Point operator-(const Point &a, const Point &b) { return Point(a.x-b.x, a.y-b.y); }
lint operator*(const Point &a, const Point &b) { return a.x*b.x + a.y*b.y; }
lint operator^(const Point &a, const Point &b) { return a.x*b.y - a.y*b.x; }

Point p[MAXN];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        cin >> p[i].x >> p[i].y;

    int ans = 0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n, k = (i + 2) % n;
        Vector u = p[j] - p[i], v = p[k] - p[i];
        if ((u ^ v) > 0) ans++;
    }

    printf("%d\n", ans);
    return 0;
}
