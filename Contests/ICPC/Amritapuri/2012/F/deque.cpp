#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;
const int MOD = (int)1e9 + 7;

lint pow2[MAXN];
lint acc[MAXN];
lint lo, hi;
set<pii, greater<pii>> intervals;
bool ok;
int n;
int ones_before[MAXN];

pll calculate(int p, int len, int q) {
    return pll((acc[n - 1 - q] * pow2[n - 2 - p]) % MOD,
               (acc[n - 1 - q] * pow2[n - 2 - (p - len + q)]) % MOD);
}

void insert(int p, int n_ones) {
    if (p == -1 || !ok) return;
    if (ones_before[p] != -1) {
        if (ones_before[p] != n_ones)
            ok = 0;
        return;
    }
    ones_before[p] = n_ones;
    intervals.insert(pii(p, n_ones));
    auto it = intervals.find(pii(p, n_ones));
    int len = p - next(it)->first;
    int q = n_ones - next(it)->second;
    if (q < 0 || q > len) {
        ok = 0;
        return;
    }
    lint add_lo, add_hi;
    tie(add_lo, add_hi) = calculate(p, len, q);
    lo += add_lo, hi += add_hi;
    lo %= MOD, hi %= MOD;
    
    if (it->first == intervals.begin()->first) return;

    int prev_len = prev(it)->first - next(it)->first;
    int prev_q = prev(it)->second - next(it)->second;
    lint rem_lo, rem_hi;
    tie(rem_lo, rem_hi) = calculate(prev(it)->first, prev_len, prev_q);
    lo -= rem_lo, hi -= rem_hi;

    prev_len = prev(it)->first - p;
    prev_q = prev(it)->second - n_ones;
    if (prev_q < 0 || prev_q > prev_len) {
        ok = 0;
        return;
    }
    tie(add_lo, add_hi) = calculate(prev(it)->first, prev_len, prev_q);
    lo += add_lo, hi += add_hi;
    lo %= MOD, hi %= MOD;
}    

int main() {
    pow2[0] = 1;
    for (int i = 1; i < MAXN; i++)
        pow2[i] = 2 * pow2[i - 1] % MOD;

    int t;
    for (scanf("%d", &t); t--;) {
        memset(ones_before, -1, sizeof(ones_before));
        scanf("%d", &n);
        acc[n - 1] = 0;
        for (int i = n - 2; i >= 0; i--)
            acc[i] = (acc[i + 1] + pow2[n - i - 2]) % MOD;
        
        intervals.clear();
        intervals.insert(pii(-1, 0));
        lo = hi = 0;
        ok = 1;
        for (int i = 0; i < n / 2; i++) {
            int p, x;
            scanf("%d%d", &p, &x);
            p--;
            int n_ones = min(x, n + 1 - x);
            if (x <= n / 2) n_ones = p + 1 - n_ones;
            insert(p, n_ones);
            insert(p - 1, n_ones - (x > n / 2));
            if (ok) printf("%lld %lld\n", (lo % MOD + MOD) % MOD,
                           (hi % MOD + MOD + acc[intervals.begin()->first + 1]) % MOD);
            else printf("-1\n");
        }
    }            
    return 0;
}
