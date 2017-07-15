#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

struct Point {
    lint x, y, z;
    Point(lint _x, lint _y, lint _z) : x(_x), y(_y), z(_z) {}
};
typedef Point Vector;

Vector operator-(const Point &p, const Point &q) {
    return Vector(p.x - q.x, p.y - q.y, p.z - q.z);
}

lint operator*(const Vector &u, const Vector &v) {
    return u.x*v.x + u.y*v.y + u.z*v.z;
}

Vector operator^(const Vector &u, const Vector &v) {
    return Vector(u.y*v.z - u.z*v.y,
                  u.z*v.x - u.x*v.z,
                  u.x*v.y - u.y*v.x);
}

long double norm(const Vector &v) {
    return sqrt((long double)(v.x*v.x + v.y*v.y + v.z*v.z));
}

int main() {
    int n;
    cin >> n;
    vector<Point> p;
    for (int i = 0; i < n; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        p.push_back(Point(x, y, z));
    }

    long double ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                Vector u = p[j] - p[i], v = p[k] - p[i];
                vector<lint> vv;
                Vector h = (u ^ v);
                for (int r = 0; r < n; r++) {
                    if (r == i || r == j || r == k) continue;                    
                    vv.push_back(h * (p[r] - p[i]));
                }
                bool ok = 1;
                for (int i = 1; i < (int)vv.size(); i++) {
                    if (vv[0] < 0 && vv[i] > 0) ok = 0;
                    if (vv[0] > 0 && vv[i] < 0) ok = 0;
                }
                if (ok) ans += norm(h) / 2;
            }
        }
    }
    printf("%.12Lf\n", ans);                        
    return 0;
}
