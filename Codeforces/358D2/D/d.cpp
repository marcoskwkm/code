#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 1010, MAXK = 12;

int dp[MAXK][MAXN][MAXN][2];
string s, t;
int n, m;

int go(int k, int i, int j, int taking) {
    if (i == n || j == m) return 0;
    if (dp[k][i][j][taking] != -1) return dp[k][i][j][taking];
    if (s[i] == t[j]) {
        if (taking) dp[k][i][j][taking] = 1 + go(k, i + 1, j + 1, 1);
        else if (k) dp[k][i][j][taking] = 1 + go(k - 1, i + 1, j + 1, 1);
    }
    return dp[k][i][j][taking] = max(dp[k][i][j][taking],
                                     max(go(k, i + 1, j, 0), go(k, i, j + 1, 0)));
}

int main() {
    int k;
    scanf("%d%d%d", &n, &m, &k);
    cin >> s >> t;
    memset(dp, -1, sizeof(dp));
    printf("%d\n", go(k, 0, 0, 0));
    return 0;
}
