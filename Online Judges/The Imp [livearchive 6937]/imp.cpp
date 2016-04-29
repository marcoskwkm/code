#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)2e5 + 10, MAXK = 20;

pii box[MAXN];
int n, k;
lint dp[MAXN][MAXK];
bool foi[MAXN][MAXK];

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        scanf("%d%d", &n,  &k);
        if (n >= MAXN) while (1);
        if (k >= MAXK) while (1);
        for (int i = 0; i < n; i++) {
            int v, c;
            scanf("%d%d", &v,  &c);
            box[i] = pii(v, c);
        }
        sort(box, box + n, [](pii a, pii b) {
            return a.first < b.first;
        });
        memset(dp, 0, sizeof(dp));
        memset(dp[n], 0, sizeof(dp[n]));
        for (int i = n - 1; i >= 0; i--) {
            for (int left = 0; left <= k; left++) {
                // take
                lint ans_take = box[i].first - box[i].second; // do not destroy
                if (left) ans_take = min(ans_take, -box[i].second + dp[i + 1][left - 1]); // destroy

                // do not take
                lint ans_dont_take = dp[i + 1][left];
                dp[i][left] = max(ans_take, ans_dont_take);
            }
        }
        printf("%lld\n", dp[0][k]);                
    }        
    return 0;
}
