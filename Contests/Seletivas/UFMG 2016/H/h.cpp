#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 110;

int dp[MAXN][MAXN];
string sa, sb;

bool go(int i, int l, int r) {
    if (dp[l][r] != -1) return dp[l][r];
    if (l == r) return dp[l][r] = (sa[i] == sb[l]);
    dp[l][r] = 0;
    if (sa[i] == sb[l]) dp[l][r] |= go(i + 1, l + 1, r);
    if (sa[i] == sb[r]) dp[l][r] |= go(i + 1, l, r - 1);
    return dp[l][r];
}

int main() {
    cin >> sa >> sb;
    int n = sa.size();
    if (sb.size() != n) {
        printf("N\n");
        return 0;
    }

    reverse(sa.begin(), sa.end());
    memset(dp, -1, sizeof(dp));
    
    printf("%s\n", go(0, 0, n - 1) ? "S" : "N");    
    return 0;
}
