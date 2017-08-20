#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e4 + 10;

int dp[MAXN][30];
int cost[30][30];
int n;

int go(int i, int last) {
    if (i == n) return 0;
    if (dp[i][last] != -1) return dp[i][last];
    int ans = INF;
    for (int j = 0; j < 26; j++)
        ans = min(ans, cost[last][j] + go(i + 1, j));
    return dp[i][last] = ans;
}        

int main() {
    cin >> n;
    for (int i = 0; i < 26; i++)
        for (int j = 0; j < 26; j++)
            scanf("%d", &cost[i][j]);
    int ans = INF;
    memset(dp, -1, sizeof(dp));
    for (int i = 0; i < 26; i++)
        ans = min(ans, go(1, i));
    cout << ans << endl;
    return 0;
}
