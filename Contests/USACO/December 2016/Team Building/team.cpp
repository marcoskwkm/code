#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 1010, MAXK = 12;
const int MOD = (int)1e9 + 9;

lint dp[MAXN][MAXN][MAXK];
lint sum[MAXN][MAXN][MAXK];
int john[MAXN], paul[MAXN];

lint go(int, int, int);

lint get_sum(int i, int j, int k) {
    if (k == 0) return 1;
    if (i < 0 || j < 0) return 0;
    if (sum[i][j][k] != -1) return sum[i][j][k];
    return sum[i][j][k] = (go(i, j, k) + get_sum(i - 1, j, k)) % MOD;
}    

lint go(int i, int j, int k) {
    if (k == 0) return 1;
    if (i < 0 || j < 0) return 0;
    if (dp[i][j][k] != -1) return dp[i][j][k];
    lint ret = go(i, j - 1, k);
    if (john[i] > paul[j]) ret += get_sum(i - 1, j - 1, k - 1);
    return dp[i][j][k] = ret % MOD;
}        

int main() {
    #ifndef HOME
    freopen("team.in", "r", stdin);
    freopen("team.out", "w", stdout);
    #endif
    
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < n; i++)
        scanf("%d", &john[i]);
    for (int i = 0; i < m; i++)
        scanf("%d", &paul[i]);
    sort(john, john + n);
    sort(paul, paul + m);
    memset(dp, -1, sizeof(dp));
    memset(sum, -1, sizeof(sum));
    printf("%lld\n", get_sum(n - 1, m - 1, k));
    return 0;
}
