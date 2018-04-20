#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e6 + 10;

int n, w, h;
vector<pii> vu, vd, vl, vr;

double xm[4 * MAXN], ym[4 * MAXN];
int nxt[4 * MAXN], side[4 * MAXN];
int n_reg;
bool in[MAXN];
int cur;

void add(int x, int y, int i) {
    if (x == 0) vl.push_back(pii(y, i));
    else if (x == w) vr.push_back(pii(y, i));
    else if (y == 0) vd.push_back(pii(x, i));
    else vu.push_back(pii(x, i));
}

void advance(int &i) {
    if (nxt[i] != n) {
        if (in[nxt[i]]) cur--;
        else cur++;
        in[nxt[i]] ^= 1;
    }
    i++;
    if (i == n_reg) i = 0;
}

int main() {
    cin >> n >> w >> h;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        add(x1, y1, i); add(x2, y2, i);
    }

    sort(vu.begin(), vu.end());
    sort(vr.begin(), vr.end(), greater<pii>());
    sort(vd.begin(), vd.end(), greater<pii>());
    sort(vl.begin(), vl.end());

    n_reg = 0;
    int last = 0;
    for (pii p: vu) {
        xm[n_reg] = double(last + p.first) / 2;
        ym[n_reg] = h;
        nxt[n_reg] = p.second;
        side[n_reg] = 0;
        last = p.first;
        n_reg++;
    }
    xm[n_reg] = double(last + w) / 2;
    ym[n_reg] = h;
    nxt[n_reg] = n;
    side[n_reg] = 0;
    n_reg++;

    last = h;
    for (pii p: vr) {
        xm[n_reg] = w;
        ym[n_reg] = double(last + p.first) / 2;
        nxt[n_reg] = p.second;
        side[n_reg] = 1;
        last = p.first;
        n_reg++;
    }
    xm[n_reg] = w;
    ym[n_reg] = double(last) / 2;
    nxt[n_reg] = n;
    side[n_reg] = 1;
    n_reg++;

    last = w;
    for (pii p: vd) {
        xm[n_reg] = double(last + p.first) / 2;
        ym[n_reg] = 0;
        nxt[n_reg] = p.second;
        side[n_reg] = 2;
        last = p.first;
        n_reg++;
    }
    xm[n_reg] = double(last) / 2;
    ym[n_reg] = 0;
    nxt[n_reg] = n;
    side[n_reg] = 2;
    n_reg++;

    last = 0;
    for (pii p: vl) {
        xm[n_reg] = 0;
        ym[n_reg] = double(last + p.first) / 2;
        nxt[n_reg] = p.second;
        side[n_reg] = 3;
        last = p.first;
        n_reg++;
    }
    xm[n_reg] = 0;
    ym[n_reg] = double(last + h) / 2;
    nxt[n_reg] = n;
    side[n_reg] = 3;
    n_reg++;

    cur = 0;
    int i1 = 0, i2 = 0;
    for (int step = 0; step < n_reg; step++) {
        while (side[i1] == side[i2]) {
            advance(i2);
        }
        while (!in[nxt[i2]] && side[i1] != side[(i2 + 1) % n_reg]) {
            advance(i2);
        }
        if (cur == n) {
            printf("1\n");
            printf("%.2f %.2f %.2f %.2f\n", xm[i1], ym[i1], xm[i2], ym[i2]);
            return 0;
        }
        advance(i1);
    }
    printf("2\n");
    printf("%.2f %.2f %.2f %.2f\n", 0.5, double(h), w - 0.5, 0.);
    printf("%.2f %.2f %.2f %.2f\n", w - 0.5, double(h), 0.5, 0.);    
    return 0;
}
