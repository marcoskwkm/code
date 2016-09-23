#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 110;

const int P = (int)1e9 + 7; 

const int MAXV = MAXN;

lint fat[MAXV], inv[MAXV], invfat[MAXV];
lint ch[MAXV][MAXV];

lint choose(int n, int k) {
    k = min(k, n - k);
    if (k < 0) return 0;
    if (ch[n][k] != -1) return ch[n][k];
    return ch[n][k] = fat[n] * invfat[k] % P * invfat[n - k] % P;
}

lint arrange(int n, int k) {
    if (k > n) return 0;
    return fat[n] * invfat[n - k] % P;
}

lint modexp(lint b, lint e) {
    lint ret = 1, aux = b;
    while (e) {
        if (e & 1) ret = ret * aux % P;
        aux = aux * aux % P;
        e >>= 1;
    }
    return ret;
}

void precalc() {
    fat[0] = fat[1] = 1;
    invfat[0] = invfat[1] = 1;
    inv[1] = 1;
    for (int n = 2; n < MAXV; n++) {
        fat[n] = fat[n - 1] * n % P;
        inv[n] = P - P/n * inv[P%n] % P;
        invfat[n] = invfat[n - 1] * inv[n] % P;
    }
}

int n, k;
lint m;
lint dp[MAXN][MAXN*MAXN];
lint qntd[MAXN];
lint memo_all[MAXN][MAXN];

lint go(int i, int q) {
    if (i == n) return q == 0;
    if (dp[i][q] != -1) return dp[i][q];
    lint ret = 0;
    int lim_take = min(n, q);
    int avail = n * (n - i - 1);
    for (int take = max(0, q - avail); take <= lim_take; take++) {
        lint all = memo_all[i][take];
        if (all == -1) {
            lint ch = choose(n, take);
            all = memo_all[i][take] = modexp(ch, qntd[i]);
        }
        ret += all * go(i + 1, q - take) % P;
    }
    return dp[i][q] = ret % P;
}

int main() {
    precalc();
    cin >> n >> m >> k;
    memset(dp, -1, sizeof(dp));
    memset(ch, -1, sizeof(ch));
    memset(memo_all, -1, sizeof(memo_all));
    for (int i = 0; i < n; i++) {
        qntd[i] = m / n;
        if (i < m % n) qntd[i]++;
    }
    cout << go(0, k) << endl;    
    return 0;
}
