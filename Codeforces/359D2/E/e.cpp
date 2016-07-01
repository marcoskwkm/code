#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;
typedef pair<pii, pll> cand;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;
const lint MAXC = 3001001001001001001ll;

struct Point {
    lint x, y, z;
    lint a, b, c, d;
    void read() {
        cin >> x >> y >> z;
        a = x + y + z;
        b = x + y - z;
        c = x - y + z;
        d = x - y - z;
        printf("point: %lld %lld %lld %lld\n", a, b, c, d);
    }
};

Point p[MAXN];
int n;

inline tuple<lint, lint, lint, lint, lint, lint, lint, lint> get_inter(lint d) {
    lint la = -3*MAXC, lb = -3*MAXC, lc = -3*MAXC, ld = -3*MAXC;
    lint ra = 3*MAXC, rb = 3*MAXC, rc = 3*MAXC, rd = 3*MAXC;
    for (int i = 0; i < n; i++) {
        la = max(la, p[i].a - d);
        ra = min(ra, p[i].a + d);
        lb = max(lb, p[i].b - d);
        rb = min(rb, p[i].b + d);
        lc = max(lc, p[i].c - d);
        rc = min(rc, p[i].c + d);
        ld = max(ld, p[i].d - d);
        rd = min(rd, p[i].d + d);
    }
    return make_tuple(la, ra, lb, rb, lc, rc, ld, rd);
}

pii candp[2][16];
pll candv[2][16];

inline tuple<lint, lint, lint, lint> get_sols(lint la, lint ra, lint lb, lint rb, lint lc, lint rc, lint ld, lint rd, bool &found) {
    int len0 = 0, len1 = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            lint aa = la + i, bb = lb + j;
            lint cc = lc + i, dd = ld + j;
            if (aa <= ra && bb <= rb && (aa & 1) == (bb & 1)) {
                candp[0][len0] = pii(((aa + bb)/2)&1, ((aa - bb)/2)&1);
                candv[0][len0++] = pll(aa, bb);
            }
            if (cc <= rc && dd <= rd && (cc & 1) == (dd & 1)) {
                candp[1][len1] = pii(((cc + dd)/2)&1, ((cc - dd)/2)&1);
                candv[1][len1++] = pll(cc, dd);
            }
        }
    }
    for (int i = 0; i < len0; i++) {
        for (int j = 0; j < len1; j++) {
            if (candp[0][i].first == candp[1][j].first && candp[0][i].second == candp[1][j].second) {
                found = 1;
                return make_tuple(candv[0][i].first, candv[0][i].second, candv[1][j].first, candv[1][j].second);
            }
        }
    }
    found = 0;
    return make_tuple(0, 0, 0, 0);
}    

inline bool check(lint d) {
    lint la, ra, lb, rb, lc, rc, ld, rd;
    tie(la, ra, lb, rb, lc, rc, ld, rd) = get_inter(d);
    if (la > ra || lb > rb || lc > rc || ld > rd) return 0;
    bool ok = 1;
    get_sols(la, ra, lb, rb, lc, rc, ld, rd, ok);
    return ok;
}

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        scanf("%d", &n);
        lint maxd = -MAXC, mind = MAXC;
        for (int i = 0; i < n; i++) {
            p[i].read();
            maxd = max(maxd, max(p[i].x, max(p[i].y, p[i].z)));
            mind = min(mind, min(p[i].x, min(p[i].y, p[i].z)));
        }
        lint l = 0, r = 3*(maxd - mind);
        while (l < r) {
            lint mid = (l + r) / 2;
            if (check(mid)) r = mid;
            else l = mid + 1;
        }
        lint la, ra, lb, rb, lc, rc, ld, rd;
        lint a, b, c, d;
        tie(la, ra, lb, rb, lc, rc, ld, rd) = get_inter(l);
        bool ok = 1;
        tie(a, b, c, d) = get_sols(la, ra, lb, rb, lc, rc, ld, rd, ok);
        assert(ok);
        lint x = ((a + b)/2 + (c + d)/2)/2;
        lint y = ((a + b)/2 - (c + d)/2)/2;
        lint z = ((a - b)/2 + (c - d)/2)/2;
        for (int i = 0; i < n; i++) {
            lint dist = abs(x - p[i].x) + abs(y - p[i].y) + abs(z - p[i].z);
            if (dist > l) {
                printf("fuck i = %d\n", i);
                printf("%lld %lld (%lld)\n", la, ra, a);
                printf("%lld %lld (%lld)\n", lb, rb, b);
                printf("%lld %lld (%lld)\n", lc, rc, c);
                printf("%lld %lld (%lld)\n", ld, rd, d);
            }
        }
        cout << x << " " << y << " " << z << endl;
    }        
    return 0;
}
