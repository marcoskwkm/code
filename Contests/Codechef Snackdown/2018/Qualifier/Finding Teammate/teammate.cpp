#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MOD = (int)1e9 + 7;
const int MAXN = (int)1e5 + 10;

lint dp[MAXN];

void precalc() {
    dp[0] = 1;
    for (int i = 2; i < MAXN; i += 2)
        dp[i] = (i - 1) * dp[i - 2] % MOD;
}

int main() {
    precalc();
    int t;
    for (scanf("%d", &t); t--;) {
        int n;
        scanf("%d", &n);
        map<int, int> mp;
        for (int i = 0; i < n; i++) {
            int s;
            scanf("%d", &s);
            mp[s]++;
        }            
        lint ans = 1;
        int off = 0;
        for (auto &p: mp) {
            int q = p.second;
            if (off) ans = ans * q % MOD;
            q -= off;
            ans = ans * dp[q & (~1)] % MOD;
            if (q & 1) {
                ans = ans * q % MOD;
                off = 1;
            }
            else off = 0;
        }
        printf("%lld\n", ans);
    }        
    return 0;
}
