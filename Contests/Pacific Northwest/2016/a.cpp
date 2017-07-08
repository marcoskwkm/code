#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 60;

int dp[MAXN][30];
char s[MAXN];
int n;

int go(int i, int j) {
    if (j == 26) return 0;
    if (i == n) return 26 - j;
    if (dp[i][j] != -1) return dp[i][j];
    if (s[i] == 'a' + j) return dp[i][j] = go(i + 1, j + 1);
    return dp[i][j] = min(go(i + 1, j), 1 + go(i, j + 1));
}

int main() {
    scanf("%s", s);
    n = strlen(s);
    memset(dp, -1, sizeof(dp));
    printf("%d\n", go(0, 0));
    return 0;
}
