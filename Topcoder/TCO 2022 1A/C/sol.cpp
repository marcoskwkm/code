#include <bits/stdc++.h>
using namespace std;

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MOD = (int)1e9 + 7;
const int MAXN = 110;

lint dp[MAXN][MAXN];
lint fact[MAXN];
lint binom[MAXN][MAXN];

lint get_binom(int n, int k) {
    k = min(k, n - k);
    if (k < 0)
        return 0;
    if (k == 0)
        return 1;
    if (binom[n][k] != -1) {
        return binom[n][k];
    }
    return binom[n][k] = (get_binom(n - 1, k - 1) + get_binom(n - 1, k)) % MOD;
}

struct SkyscraperCounting {
    int count(string visibility) {
        int n = visibility.size();

        fact[0] = 1;
        for (int i = 1; i < MAXN; i++) {
            fact[i] = fact[i - 1] * i % MOD;
        }

        memset(dp, 0, sizeof(dp));
        memset(binom, -1, sizeof(binom));
        int prv_i = -1;
        int x_cnt = 0;
        for (int i = n - 1; i >= 0; i--) {
            if (visibility[i] == 'X') {
                x_cnt++;
                continue;
            }

            if (prv_i == -1) {
                dp[i][0] = fact[n - i - 1];
                prv_i = i;
                continue;
            }

            int inter_x = prv_i - i - 1;
            for (int k = 0; k < n; k++) {
                if (dp[prv_i][k] == 0) {
                    continue;
                }

                for (int w = k + 1; w < n; w++) {
                    int fixed_x = w - k - 1;
                    if (fixed_x > x_cnt - inter_x) {
                        break;
                    }
                    lint add = dp[prv_i][k] * fact[inter_x] % MOD;
                    lint rem = n - i - w - 1;
                    add = add * get_binom(rem, inter_x) % MOD;
                    dp[i][w] += add;
                    dp[i][w] %= MOD;
                }
            }
            prv_i = i;
        }

        lint ans = 0;
        for (int i = 0; i < n; i++)
            ans += dp[0][i];

        return ans % MOD;
    }
};

#ifdef HOME
int main() {
    string visibility;
    cin >> visibility;
    cout << SkyscraperCounting().count(visibility) << endl;
    return 0;
}
#endif
