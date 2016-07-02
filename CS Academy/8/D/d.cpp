#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;
const int MAXV = (int)1e5 + 10;

struct Point {
    int x, y;
    void read() {
        scanf("%d%d", &x, &y);
    }
};

Point p[MAXN];
int n;
int bit[MAXV];
int bitx[MAXV], bity[MAXV];

int query(int *v, int i) {
    i = min(i, MAXV - 1);
    int ret = 0;
    for (; i > 0; i -= i & -i)
        ret += v[i];
    return ret;
}

void update(int *v, int i, int val) {
    for (; i < MAXV; i += i & -i)
        v[i] += val;
}

lint get_count(int d) {
    memset(bit, 0, sizeof(bit));
    memset(bitx, 0, sizeof(bitx));
    memset(bity, 0, sizeof(bity));
    int l = 0;
    lint ret = 0;
    for (int r = 0; r < n; r++) {
        while (l < r && p[l].x + d < p[r].x) {
            update(bit, p[l].y, -1);
            l++;
        }
        int qx = query(bitx, p[r].x + d) - query(bitx, p[r].x - d - 1);
        int qy = query(bity, p[r].y + d) - query(bity, p[r].y - d - 1);
        int qs = query(bit, p[r].y + d) - query(bit, p[r].y - d - 1);
        ret += qx + qy - qs;
        update(bit, p[r].y, 1);
        update(bitx, p[r].x, 1);
        update(bity, p[r].y, 1);
    }
    return ret;
}        

int main() {
    lint k;
    scanf("%d%lld", &n, &k);
    for (int i = 0; i < n; i++) p[i].read();
    sort(p, p + n, [](Point a, Point b) {
        return a.x < b.x;
    });
    int l = 0, r = 10*MAXV;
    while (l < r) {
        int mid = (l + r)/2;
        if (get_count(mid) < k) l = mid + 1;
        else r = mid;
    }
    printf("%d\n", l);
    return 0;
}
