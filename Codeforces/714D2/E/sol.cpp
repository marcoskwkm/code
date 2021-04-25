#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr, args)
#define readIntArray(v, n) for_each(v.begin(), v.begin() + n, [](int &x) { scanf("%d", &x); })
#define readLintArray(v, n) for_each(v.begin(), v.begin() + n, [](int &x) { scanf("%lld", &x); })

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;
const int MOD = (int)1e9 + 7;

lint fact[MAXN];

lint modexp(lint b, lint e, lint m) {
    lint ret = 1;
    while (e) {
        if (e & 1)
            ret = (ret * b) % m;
        b = (b * b) % m;
        e >>= 1;
    }
    return (ret % m + m) % m;
}

void precalc() {
    fact[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }
}

int main() {
    precalc();

    int n;
    cin >> n;
    vector<int> v(n);
    readIntArray(v, n);

    lint sum = 0;
    for_each(v.begin(), v.end(), [&](int x) { sum += x; });
    if (sum % n) {
        printf("0\n");
        return 0;
    }

    map<int, int> freq;
    for_each(v.begin(), v.end(), [&](int x) { freq[x]++; });

    lint avg = sum / n;
    lint n_sinks = count_if(v.begin(), v.end(), [&](int x) { return x < avg; });
    lint n_sources = count_if(v.begin(), v.end(), [&](int x) { return x > avg; });
    lint n_avg = n - n_sinks - n_sources;

    lint ans;
    if (min(n_sinks, n_sources) <= 1) {
        ans = fact[n];
    } else {
        ans = fact[n_sinks] * fact[n_sources] % MOD;
        ans = ans * fact[n_avg] % MOD;
        ans = ans * fact[n] % MOD;
        ans = ans * modexp(fact[n_sinks + n_sources], MOD - 2, MOD) % MOD;
        ans = ans * modexp(fact[n_avg], MOD - 2, MOD) % MOD;
        ans = 2 * ans % MOD;
    }

    for (auto [_, f] : freq) {
        ans = ans * modexp(fact[f], MOD - 2, MOD) % MOD;
    }

    printf("%lld\n", ans);
    return 0;
}
