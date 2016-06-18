#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MOD = (int)1e9 + 9;

int main() {
    int t = 1, T;
    for (scanf("%d", &T); t <= T; t++) {
        debug("Test %d (out of %d)...\n", t, T);
        lint c, s;
        scanf("%lld%lld", &c, &s);
        lint ans = 0;
        if (c == 1) {
            for (lint a = 0; a <= s; a++)
                ans += s - a + 1;
        }
        else {
            for (int b = 0; b <= s; b++) {
                int mind = ((c - 2)*b + (c - 2)) / (c - 1);
                lint qa = s - b + 1;
                ans += qa * (2*s - b - mind + 3) % MOD * (b - mind) % MOD;
                ans += qa * (s - b + 1) % MOD;
            }
        }                
        printf("%lld\n", ans % MOD);
    }            
    return 0;
}
