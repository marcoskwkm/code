#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int go(vector<pii> &v, int l, int r) {
    sort(v.begin(), v.end());
    int ans = 0;
    int best = -INF;
    int cur = l;
    for (pii p: v) {
        if (p.first > cur) {
            ans++;
            cur = best + 1;
            if (cur > r) break;
            if (p.first > cur) return INF;
        }
        best = max(best, p.second);
    }
    if (cur <= r) {
        if (best < r) return INF;
        ans++;
    }
    return ans;
}                

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        int n, k, m;
        scanf("%d%d%d", &n, &k, &m);
        vector<pii> v, h;
        for (int i = 0; i < m; i++) {
            int x1, y1, x2, y2;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            v.push_back(pii(min(y1, y2), max(y1, y2)));
            h.push_back(pii(min(x1, x2), max(x1, x2)));
        }
        int ansh = go(h, (n - k)/2 + 1, (n - k)/2 + k);
        int ansv = go(v, (n - k)/2 + 1, (n - k)/2 + k);
        if (ansh == INF || ansv == INF) printf("-1\n");
        else printf("%d\n", ansh + ansv);
    }        
    return 0;
}
