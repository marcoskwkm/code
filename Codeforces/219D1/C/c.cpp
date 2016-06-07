#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1.5e5 + 10, MAXM = 310;

lint dp[2][MAXN];

int n, m, d;
int a[MAXN], t[MAXN];

int main() {
    scanf("%d%d%d", &n, &m, &d);
    lint ans = 0;
    for (int i = 1; i <= m; i++) {
        int b;
        scanf("%d%d%d", &a[i], &b, &t[i]);
        ans += b;
    }

    t[0] = 1;
    int cur = 0, nxt = 1;

    for (int i = 1; i <= m; i++) {
        lint dt = t[i] - t[i - 1];
        deque<pll> best;
        int at = 1;
        for (int p = 1; p <= n; p++) {
            while (best.size() > 0 && best.front().second < p - dt * d) best.pop_front();
            while (at <= n && at <= p + dt * d) {
                while (best.size() > 0 && best.back().first <= dp[cur][at])
                    best.pop_back();
                best.push_back(pll(dp[cur][at], at));
                at++;
            }
            dp[nxt][p] = best.front().first - abs(a[i] - p);
        }
        cur ^= 1;
        nxt ^= 1;
    }

    lint rem = -LINF;
    for (int i = 1; i <= n; i++)
        rem = max(rem, dp[cur][i]);

    cout << ans + rem << endl;        
    return 0;
}
