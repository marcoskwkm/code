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
const int MAXN = (int)2e5 + 10;
const int MOD = (int)1e9 + 7;

array<lint, MAXN> fact;

int main() {
    fact[0] = 1;
    for (int i = 1; i < MAXN; i++)
        fact[i] = fact[i - 1] * i % MOD;

    int t;
    for (cin >> t; t--;) {
        int n;
        cin >> n;
        vector<int> v(n);
        readIntArray(v, n);
        int and_all = v[0];
        for_each(v.begin(), v.end(), [&](int x) { and_all &= x; });

        lint and_cnt = count(v.begin(), v.end(), and_all);
        if (and_cnt < 2) {
            printf("0\n");
            continue;
        }

        lint ans = and_cnt * (and_cnt - 1) % MOD * fact[n - 2] % MOD;
        printf("%lld\n", ans);
    }
    return 0;
}
