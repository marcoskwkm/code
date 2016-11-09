#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef pair<double, int> pdi;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;
const double EPS = 1e-9;

pdi event[2 * MAXN];

int main() {
#ifndef HOME
    freopen("walk.in", "r", stdin);
#endif

    int t;
    for (scanf("%d", &t); t--;) {
        int n, R;
        scanf("%d%d", &n, &R);
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            int x, y, r;
            scanf("%d%d%d", &x, &y, &r);
            int r2 = R - r;
            if (r2 < 0) continue;
            if (r2 == 0) {
                if (y == 0) {
                    event[cnt++] = pdi(x, r);
                    event[cnt++] = pdi(x + EPS, -r);
                }
            }
            else {
                if (abs(y) > r2) continue;
                double rr = sqrt(double(r2)*double(r2) - double(y)*double(y));
                event[cnt++] = pdi(x - rr, r);
                event[cnt++] = pdi(x + rr, -r);
            }
        }
        lint ans = 0, cur = 0;
        sort(event, event + cnt, [](pdi a, pdi b) {
            if (a.first == b.first) return a.second > b.second;
            return a.first < b.first;
        });
        
        for (int i = 0; i < cnt; i++) {
            cur += event[i].second;
            ans = max(ans, cur);
        }
        cout << ans << endl;
    }        
    return 0;
}
