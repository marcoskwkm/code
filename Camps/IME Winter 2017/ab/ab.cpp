#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MOD = (int)1e9 + 9;
const int MAXN = 1010;

lint dp[MAXN][2 * MAXN][2];
string s;
int n;

lint go(int i, int diff, int k) {
    if (i == n) return 0;
    if (dp[i][diff][k] != -1) return dp[i][diff][k];
    if (k && s[i] != 'b') return dp[i][diff][k] = go(i + 1, diff, k);
    if (!k && s[i] != 'a') return dp[i][diff][k] = go(i + 1, diff, k);
    int ndiff = diff + (k ? 1 : -1);
    lint ret = (ndiff == MAXN ? 1 : 0);
    ret += go(i + 1, ndiff, k) + go(i + 1, ndiff, k ^ 1);
    // printf("dp[%d][%d][%d] = %lld\n", i, diff - MAXN, k, ret);
    return dp[i][diff][k] = ret % MOD;
}

int main() {
    cin >> s;
    n = s.size();
    memset(dp, -1, sizeof(dp));
    cout << ((go(0, MAXN, 0) + go(0, MAXN, 1) + 1) % MOD + MOD ) % MOD << endl;    
    return 0;
}
