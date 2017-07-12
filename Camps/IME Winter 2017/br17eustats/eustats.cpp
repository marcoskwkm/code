#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)2.5e5 + 10;

vector<int> merge_tree[4 * MAXN];

void insert(int i, int l, int r, int x, int y) {
    if (x < l || x > r) return;
    // printf("insert [%d, %d], (%d, %d)\n", l, r, x, y);
    merge_tree[i].push_back(y);
    if (l == r) return;
    int L = 2*i + 1, R = 2*i + 2, mid = (l + r) / 2;
    insert(L, l, mid, x, y); insert(R, mid + 1, r, x, y);
}

int query(int i, int l, int r, int xl, int xr, int yl, int yr) {
    if (xl > r || xr < l) return 0;
    // printf("query [%d, %d], (%d, %d), (%d, %d)\n", l, r, xl, xr, yl, yr);
    if (xl <= l && r <= xr) {
        return upper_bound(merge_tree[i].begin(), merge_tree[i].end(), yr) -
            upper_bound(merge_tree[i].begin(), merge_tree[i].end(), yl - 1);
        return 0;
    }
    int L = 2*i + 1, R = 2*i + 2, mid = (l + r) / 2;
    return query(L, l, mid, xl, xr, yl, yr) +
        query(R, mid + 1, r, xl, xr, yl, yr);
}

int main() {
    int n;
    cin >> n;
    vector<pii> v;
    vector<int> vx;
    for (int i = 0; i < n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        v.push_back(pii(x, y));
        vx.push_back(x);
    }
    sort(vx.begin(), vx.end());
    map<int, int> mx;
    vx.erase(unique(vx.begin(), vx.end()), vx.end());

    int nx = vx.size();
    for (int i = 0; i < nx; i++)
        mx[vx[i]] = i;

    for (pii p: v) insert(0, 0, nx - 1, mx[p.first], p.second);
    for (int i = 0; i < 4 * n; i++)
        sort(merge_tree[i].begin(), merge_tree[i].end());

    vector<int> ans(4, 0);
    int q = 4, Q;
    for (cin >> Q; q < Q + 4; q++) {
        int e, f, g, h;
        scanf("%d%d%d%d", &e, &f, &g, &h);
        int a = e ^ ans[q - 4];
        int b = f ^ ans[q - 3];
        int c = g ^ ans[q - 2];
        int d = h ^ ans[q - 1];

        if (a > b) swap(a, b);
        if (c > d) swap(c, d);
        
        int l = 0, r = nx;
        while (l < r) {
            int mid = (l + r) / 2;
            if (vx[mid] >= a) r = mid;
            else l = mid + 1;
        }
        int ql = l;

        l = -1, r = nx - 1;
        while (l < r) {
            int mid = (l + r + 1) / 2;
            if (vx[mid] <= b) l = mid;
            else r = mid - 1;
        }
        int qr = l;
        // printf("(%d, %d), (%d, %d)\n", ql, qr, c, d);

        if (ql > qr) {
            ans.push_back(0);
            printf("%d\n", 0);
        }
        else {
            ans.push_back(query(0, 0, nx - 1, ql, qr, c, d));
            printf("%d\n", ans[q]);
        }
    }    
    return 0;
}
