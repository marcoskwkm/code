#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 210;

double dp[MAXN][MAXN][MAXN];
double dp2[MAXN][MAXN];
double p[MAXN];
int prize[MAXN];
int n, l, k;

int main() {
    scanf("%d%d%d", &n, &l, &k);
    memset(dp, 0, sizeof(dp));
    dp[0][0][k] = 1;
    dp2[0][0] = 1;
    for (int i = 0; i < n; i++) {
        scanf("%lf", &p[i]);
        p[i] /= 100;
    }
    for (int i = 0; i < n; i++)
        scanf("%d", &prize[i]);
    
    for (int i = 0; i < n; i++) {
        for (int q = 0; q < n; q++) {
            if (prize[i] == -1) {
                // win
                dp2[i + 1][q + 1] += dp2[i][q] * p[i];

                // lose
                dp2[i + 1][q] += dp2[i][q] * (1 - p[i]);
            }
            else {
                dp2[i + 1][q] = dp2[i][q];
            }
        }
        for (int q = 0; q < n; q++) {
            for (int bag = 0; bag < MAXN; bag++) {
                if (prize[i] != -1) {
                    // win
                    int nxtbag = bag;
                    if (prize[i] != -1) nxtbag = max(nxtbag, prize[i]);
                    dp[i + 1][q + 1][nxtbag] += p[i] * dp[i][q][bag];

                    // lose
                    dp[i + 1][q][bag] += (1 - p[i]) * dp[i][q][bag];
                }
                else {
                    dp[i + 1][q][bag] = dp[i][q][bag];
                }
            }
        }
    }

    double ans = 0;
    for (int q1 = 0; q1 <= n; q1++) {
        for (int q2 = 0; q2 <= n; q2++) {
            if (q1 + q2 < l) continue;
            for (int bag = q2; bag < MAXN; bag++)
                ans += dp[n][q1][bag] * dp2[n][q2];
        }
    }
    printf("%.10f\n", ans);    
    return 0;
}
