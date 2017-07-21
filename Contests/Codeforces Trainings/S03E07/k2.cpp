#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 4000;
const int MOD = (int)1e9 + 7;

int d, k;
lint dp[MAXN][MAXN];
lint acc[MAXN][MAXN], acc2[MAXN][MAXN];

lint go(int, int);

lint go_acc2(int i, int j) {
    if (i < 0 || j < 0) return 0;
    if (acc2[i][j] != -1) return acc2[i][j];
    return acc2[i][j] = (go(i, j) + go_acc2(i - 1, j - 1)) % MOD;
}

lint go_acc(int i, int j) {
    if (i < 0) return 0;
    if (acc[i][j] != -1) return acc[i][j];
    return acc[i][j] = (go(i, j) + go_acc(i - 1, j)) % MOD;
}

lint go(int i, int j) {
    if (i == 0) return j == 0;
    if (dp[i][j] != -1) return dp[i][j];
    dp[i][j] = (k - 1) * (go_acc(i - 1, j) - go_acc(i - d, j) +
                          go_acc2(i - d, j - (i - d + 1))) % MOD;
    return dp[i][j] = (dp[i][j] + MOD) % MOD;
}

lint modexp(lint b, lint e) {
    lint ret = 1, aux = b;
    while (e) {
        if (e & 1) ret = ret * aux % MOD;
        aux = aux * aux % MOD;
        e >>= 1;
    }
    return ret;
}

int main() {
    int n, t;
    cin >> n >> d >> t >> k;
    memset(dp, -1, sizeof(dp));
    memset(acc, -1, sizeof(acc));
    memset(acc2, -1, sizeof(acc2));
    lint ans = go(n, t);
    cout << ans * modexp(k - 1, MOD - 2) % MOD * k % MOD << endl;
    return 0;
}
