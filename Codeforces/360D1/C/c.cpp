#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 510;

bool dp[2][MAXN][MAXN];

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    int cur = 0, prv = 1;
    dp[prv][0][0] = 1;
    for (int i = 0; i < n; i++) {
        memset(dp[cur], 0, sizeof(dp[cur]));
        int v;
        scanf("%d", &v);
        for (int ink = 0; ink <= k; ink++) {
            for (int inx = 0; inx <= ink; inx++) {
                if (!dp[prv][ink][inx]) continue;
                dp[cur][ink][inx] = 1;
                if (ink + v <= k) {
                    dp[cur][ink + v][inx] = 1;
                    dp[cur][ink + v][inx + v] = 1;
                }
            }
        }
        cur ^= 1, prv ^= 1;
    }
    vector<int> ans;
    for (int x = 0; x <= k; x++)
        if (dp[prv][k][x]) ans.push_back(x);
    printf("%d\n", ans.size());
    for (int i = 0; i < (int)ans.size(); i++)
        printf("%d%c", ans[i], " \n"[i + 1 == ans.size()]);    
    return 0;
}
