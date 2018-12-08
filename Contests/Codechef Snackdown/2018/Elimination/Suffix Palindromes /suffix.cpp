#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 1010;

lint cnt[MAXN];
lint dp[MAXN];
lint pot[MAXN];

int main() {
    int n, s, m;
    cin >> n >> s >> m;
    cnt[1] = s;
    pot[0] = 1;
    for (int i = 1; i <= n; i++)
        pot[i] = pot[i - 1] * s % m;
    
    dp[1] = s;
    lint ans = pot[n];
    for (int size = 2; size <= n; size++) {
        int half = (size + 1) / 2;
        lint q = pot[half];
        for (int pref = 2; pref <= half; pref++)
            q -= dp[pref] * pot[half - pref] % m;
        dp[size] = (q % m + m) % m;
        ans -= dp[size] * pot[n - size] % m;
        // debug("dp[%d] = %lld\n", size, dp[size]);
    }

    cout << (ans % m + m) % m << endl;
    return 0;
}
