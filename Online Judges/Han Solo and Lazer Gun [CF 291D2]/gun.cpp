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
    Point () {}
    Point (lint xx, lint yy) { x = xx; y = yy; }
};

typedef Point Vector;

Point operator-(const Point &a, const Point &b) { return Point(a.x-b.x, a.y-b.y); }
lint operator*(const Point &a, const Point &b) { return a.x*b.x + a.y*b.y; }
lint operator^(const Point &a, const Point &b) { return a.x*b.y - a.y*b.x; }

Point p[MAXN];
bool foi[MAXN];

int main() {
    Point o;
    int n;
    cin >> n >> o.x >> o.y;
    for (int i = 0; i < n; i++)
        cin >> p[i].x >> p[i].y;

    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (foi[i]) continue;
        ans++;
        for (int j = i; j < n; j++) {
            Vector u = p[j] - o, v = p[i] - o;
            if ((u ^ v) == 0) foi[j] = 1;
        }
    }
    
    printf("%d\n", ans);    
    return 0;
}
