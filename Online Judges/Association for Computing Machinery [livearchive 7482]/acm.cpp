#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 15, MAXT = 330;

int solve_t[MAXN];
int dp[1 << 15][MAXT];

int main() {
    int n, p;
    while (scanf("%d%d", &n, &p) > 0) {
        for (int i = 0; i < n; i++)
            scanf("%d", &solve_t[i]);
        if (solve_t[p] > 300) {
            printf("0 0\n");
            continue;
        }
        memset(dp, INF, sizeof(dp));
        dp[1 << p][solve_t[p]] = solve_t[p];
        int ans_ac = 0, ans_pen = INF;
        for (int t = solve_t[p]; t <= 300; t++) {
            for (int mask = (1 << p); mask < (1 << n); mask++) {
                if (dp[mask][t] == INF) continue;
                if (__builtin_popcount(mask) > ans_ac) {
                    ans_ac = __builtin_popcount(mask);
                    ans_pen = dp[mask][t];
                }
                else if(__builtin_popcount(mask) == ans_ac)
                    ans_pen = min(ans_pen, dp[mask][t]);
                for (int i = 0; i < n; i++) {
                    if (mask & (1 << i)) continue;
                    if (t + solve_t[i] > 300) continue;
                    int nxt = mask ^ (1 << i);
                    dp[nxt][t + solve_t[i]] = min(dp[nxt][t + solve_t[i]], dp[mask][t] + t + solve_t[i]);
                }
            }
        }
        printf("%d %d\n", ans_ac, ans_pen);
    }        
    return 0;
}
