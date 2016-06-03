#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXD = 310;
const int MAXP = MAXD*MAXD;

int tree[4][MAXD][MAXD];
int n, m, p;

void update(int r, int c, int val, bool force = false) {
    r++; c++;
    for (int k = 0; k < 4; k++) {
        int R = r, C = c, add = 0;
        if (k == 0) add = -r - c;
        if (k == 1) C = MAXD - c, add = -r + c;
        if (k == 2) R = MAXD - r, add = r - c;
        if (k == 3) C = MAXD - c, R = MAXD - r, add = r + c;
        for (int rr = R; rr < MAXD; rr += rr & -rr) {
            for (int cc = C; cc < MAXD; cc += cc & -cc) {
                if (force) tree[k][rr][cc] = val + add;
                else tree[k][rr][cc] = min(tree[k][rr][cc], val + add);
            }
        }
    }
}

int query(int r, int c) {
    r++; c++;
    int ret = INF;
    for (int k = 0; k < 4; k++) {
        int R = r, C = c, add = 0;
        if (k == 0) add = r + c;
        if (k == 1) C = MAXD - c, add = r - c;
        if (k == 2) R = MAXD - r, add = -r + c;
        if (k == 3) C = MAXD - c, R = MAXD - r, add = -r - c;
        for (int rr = R; rr > 0; rr -= rr & -rr)
            for (int cc = C; cc > 0; cc -= cc & -cc)
                ret = min(ret, tree[k][rr][cc] + add);
    }
    return ret;
}

vector<pii> pos[MAXP];
int bests[MAXD*MAXD];

int main() {
    scanf("%d%d%d", &n, &m, &p);
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            int x;
            scanf("%d", &x);
            pos[x].push_back(pii(r, c));
        }
    }
    memset(tree, INF, sizeof(tree));
    int rp = pos[p][0].first, cp = pos[p][0].second;
    update(rp, cp, 0);
    for (int pp = p - 1; pp >= 1; pp--) {
        int cnt = 0;
        for (pii &chest: pos[pp]) {
            int r = chest.first, c = chest.second;
            bests[cnt++] = query(r, c);
        }
        for (const pii &mp: pos[pp + 1])
            update(mp.first, mp.second, INF, true /* force */);
        for (int i = 0; i < (int)pos[pp].size(); i++) 
            update(pos[pp][i].first, pos[pp][i].second, bests[i]);
    }
    printf("%d\n", query(0, 0));
    return 0;
}
