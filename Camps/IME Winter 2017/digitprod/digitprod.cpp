#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 110, MOD = (int)1e9 + 7;

const int p[] = {2, 3, 5, 7};
int q[4];
lint fat[MAXN], ifat[MAXN], inv[MAXN];

lint modexp(lint b, lint e) {
    lint ret = 1, aux = b;
    while (e) {
        if (e & 1) ret = ret * aux % MOD;
        aux = aux * aux % MOD;
        e >>= 1;
    }
    return ret;
}

void precalc() {
    fat[0] = fat[1] = ifat[0] = ifat[1] = 1;
    inv[1] = 1;
    for (int n = 2; n < MAXN; n++) {
        fat[n] = fat[n - 1] * n % MOD;
        inv[n] = MOD - MOD/n * inv[MOD%n] % MOD;
        ifat[n] = ifat[n - 1] * inv[n] % MOD;
    }
}

int n_digits[10];
lint go(int i) {
    lint ret = 0;
    if (i == 3) {
        int total = 0;
        for (int d = 2; d <= 9; d++)
            total += n_digits[d];
        for (int n1 = 0; n1 + total <= 100; n1++) {
            if (n1 + total == 0) continue;
            n_digits[1] = n1;
            lint got = fat[n1 + total];
            for (int d = 1; d <= 9; d++)
                got = got * ifat[n_digits[d]] % MOD;
            ret += got;
        }
        return ret;
    }
    if (i == 0) {
        for (int q4 = 0; 2*q4 <= q[0]; q4++) {
            for (int q8 = 0; 2*q4 + 3*q8 <= q[0]; q8++) {
                n_digits[4] = q4;
                n_digits[8] = q8;
                n_digits[2] = q[0] - 2*q4 - 3*q8;
                ret += go(i + 1);
            }
        }
        return ret % MOD;
    }
    if (i == 1) {
        for (int q9 = 0; 2*q9 <= q[1]; q9++) {
            n_digits[9] = q9;
            n_digits[3] = q[1] - 2*q9;
            ret += go(i + 1);
        }
        return ret % MOD;
    }
    if (i == 2) {
        for (int q6 = 0; q6 <= n_digits[2] && q6 <= n_digits[3]; q6++) {
            n_digits[6] = q6;
            n_digits[2] -= q6;
            n_digits[3] -= q6;
            ret += go(i + 1);
            n_digits[3] += q6;
            n_digits[2] += q6;
            n_digits[6] = 0;
        }
        return ret % MOD;
    }
}

int main() {
    precalc();
    int t;
    for (scanf("%d", &t); t--;) {
        lint n;
        cin >> n;
        if (n == 0) {
            lint ans = 1;
            for (int nd = 2; nd <= 100; nd++)
                ans += 9 * modexp(10, nd - 1) - modexp(9, nd);
            ans = (ans % MOD + MOD) % MOD;
            cout << ans << endl;
            continue;
        }                
                
        memset(q, 0, sizeof(q));
        for (int i = 0; i < 4; i++) {
            while (n % p[i] == 0) {
                n /= p[i];
                q[i]++;
            }
        }
        if (n > 1) {
            printf("0\n");
            continue;
        }
        n_digits[5] = q[2];
        n_digits[7] = q[3];
        cout << go(0) << endl;
    }        
    return 0;
}
