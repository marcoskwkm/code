#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

struct Point {
    lint x, y;
    Point(lint xx = 0, lint yy = 0) { x = xx, y = yy; }
};

typedef Point Vector;

Vector operator-(Point a, Point b) { return Point(a.x - b.x, a.y - b.y); }
Point operator+(Point a, Point b) { return Point(a.x + b.x, a.y + b.y); }
bool operator==(Point a, Point b) { return a.x == b.x && a.y == b.y; }
lint operator*(Vector u, Vector v) { return u.x*v.x + u.y*v.y; }
lint operator^(Vector u, Vector v) { return u.x*v.y - u.y*v.x; }
lint norm2(Vector u) { return u.x*u.x + u.y*u.y; }
int sign(lint n) { return n ? n / abs(n) : 0; }

int main() {
    Point P[9];
    for (int i = 1; i <= 7; i++)
        scanf("%lld%lld", &P[i].x, &P[i].y);
    bool ok = 1;
    ok = ok && (P[2] - P[1]) * (P[3] - P[1]) > 0;
    ok = ok && norm2(P[2] - P[1]) == norm2(P[3] - P[1]);
    ok = ok && ((P[3] - P[2]) ^ (P[4] - P[2])) == 0 && ((P[3] - P[2]) ^ (P[5] - P[2])) == 0;
    ok = ok && (P[2] + P[3]) == (P[4] + P[5]);
    ok = ok && norm2(P[3] - P[2]) > norm2(P[5] - P[4]);
    ok = ok && (P[6] - P[4]) * (P[3] - P[2]) == 0 && (P[7] - P[5]) * (P[3] - P[2]) == 0;
    ok = ok && norm2(P[6] - P[4]) == norm2(P[7] - P[5]);
    ok = ok && sign((P[3] - P[2]) ^ (P[1] - P[2])) != sign((P[3] - P[2]) ^ (P[6] - P[1]));

    printf("%c\n", ok ? 'S' : 'N');    
    return 0;
}
