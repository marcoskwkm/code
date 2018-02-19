#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

const int P = (int)1e9 + 7; 

const int MAXV = (int)2e6 + 10;

lint fat[MAXV], inv[MAXV], invfat[MAXV];

lint choose(int n, int k) {
    k = min(k, n - k);
    if (k < 0) return 0;
    return fat[n] * invfat[k] % P * invfat[n - k] % P;
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

lint split(lint n, lint k) {
    lint ret = fat[n];
    return ret * choose(n + k - 1, n) % P;
}

int main() {
    lint m, w, p;
    scanf("%lld%lld%lld", &m, &w, &p);
    precalc();

    if (m == 0) printf("%lld\n", fat[w]);
    else if (w == 0) printf("%lld\n", fat[m]);
    else {
        lint ans = 0;
        for (int f = 1; f <= p; f++) {
            lint fixed = arrange(p, f);
            int n1 = (f + 1) / 2;
            int n2 = f + 1 - n1;
            ans += fixed * split(m - f, n1) % P * split(w - f, n2) % P;
            ans %= P;
            ans += fixed * split(w - f, n1) % P * split(m - f, n2) % P;
            ans %= P;
        }
        printf("%lld\n", ans);
    }
    return 0;    
}
