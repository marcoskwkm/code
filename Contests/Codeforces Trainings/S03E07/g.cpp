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
const int MAXN = 210;

lint inv[MAXN], invF[MAXN];

lint choose(lint n, lint k) {
    k = min(k, n - k);
    if (k < 0) return 0;
    lint ret = 1;
    for (int i = 0; i < k; i++)
        ret = ret * (n - i) % MOD;
    ret = ret * invF[k] % MOD;
    return ret;
}

void precalc() {
    invF[0] = invF[1] = 1;
    inv[1] = 1;
    for (int n = 2; n < MAXN; n++) {
        inv[n] = MOD - MOD/n * inv[MOD % n] % MOD;
        invF[n] = invF[n - 1] * inv[n] % MOD;
    }
}

int main() {
    precalc();
    int n, a, b, x;
    scanf("%d%d%d%d", &n, &a, &b, &x);
    vector<int> factors;
    int cx = x;
    for (int d = 2; d * d <= cx; d++) {
        if (cx % d) continue;
        int factor = 1;
        do {
            factor *= d;
            cx /= d;
        } while (cx % d == 0);
        factors.push_back(factor);
    }
    if (cx > 1) factors.push_back(cx);
    
    int k = factors.size();
    lint total = choose(n + b - a, n);
    for (int mf = 1; mf < (1 << k); mf++) {
        vector<int> active;
        for (int i = 0; i < k; i++)
            if (mf & (1 << i))
                active.push_back(factors[i]);
        int l = active.size();
        int n_avail = b - a + 1;
        for (int ma = 1; ma < (1 << l); ma++) {
            int prod = 1;
            for (int i = 0; i < l; i++)
                if (ma & (1 << i))
                    prod *= active[i];
            int val = b / prod - (a - 1) / prod;
            if (__builtin_popcount(ma) & 1) n_avail -= val;
            else n_avail += val;
        }
        lint add = choose(n + n_avail - 1, n);
        if (__builtin_popcount(mf) & 1) total -= add;
        else total += add;
        total %= MOD;
    }

    cout << (total + MOD) % MOD << endl;    
    return 0;
}
