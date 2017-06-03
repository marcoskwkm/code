#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 300;
const int MAXV = (int)2e9;

lint u[MAXN], v[MAXN];
int n, m, k;

int go(lint delta) {
    int ans = 0;
    int at = 0;
    for (int i = 0; i < m; i++) {
        while (at < n && u[at] + delta < v[i] - k) at++;
        if (at == n) break;
        if (u[at] + delta <= v[i] + k) {
            at++;
            ans++;
        }
    }
    return ans;
}                                    

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        scanf("%d%d%d", &n, &m, &k);
        for (int i = 0; i < n; i++) scanf("%lld", &u[i]);
        for (int i = 0; i < m; i++) scanf("%lld", &v[i]);
        sort(u, u + n); sort(v, v + m);

        int ans =  0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                lint delta = v[j] - u[i] - k;
                if (delta < -MAXV || delta > MAXV) continue;
                ans = max(ans, go(delta));
                delta = v[j] - u[i] + k;
                if (delta < -MAXV || delta > MAXV) continue;
                ans = max(ans, go(delta));
            }
        }

        printf("%d\n", ans);
    }        
    return 0;
}
