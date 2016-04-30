#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 210;

int x[MAXN], y[MAXN];

int main() {
    int t = 1, T;
    for (scanf("%d", &T); t <= T; t++) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) scanf("%d", &x[i]);
        for (int i = 0; i < n; i++) scanf("%d", &y[i]);
        vector<pii> events;
        int cur = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int k;
                scanf("%d", &k);
                if (i == j) continue;
                int d = (x[i] - x[j])*(x[i] - x[j]) + (y[i] - y[j])*(y[i] - y[j]);
                if (k) {
                    events.push_back(pii(d, -1));
                    cur++;
                }
                else events.push_back(pii(d, 1));
            }
        }
        sort(events.begin(), events.end());
        pii ans(cur, 0);
        int last = 0;
        for (int i = 0; i < (int)events.size(); i++) {
            cur += events[i].second;
            if (i + 1 < (int)events.size() && events[i + 1].first == events[i].first)
                continue;
            ans = min(ans, pii(cur, events[i].first));
        }
        printf("Case #%d: %d %d\n", t, ans.second, ans.first);
    }                
    return 0;
}
