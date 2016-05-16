#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)2e5 + 10;
const int MOD = (int)1e6 + 3;
const int MODRT = 1000;

int l[MAXN], t[MAXN];
int inv[MOD];
lint invfat[MOD];

lint modexp(lint b, lint e) {
    lint ret = 1, aux = b;
    while (e) {
        if (e & 1) ret = ret * aux % MOD;
        e >>= 1;
        aux = (aux * aux) % MOD;
    }
    return ret;
}

void precalc() {
    inv[1] = 1;
    invfat[1] = 1;
    for (int i = 2; i < MOD; i++) {
        inv[i] = modexp(i, MOD - 2);
        invfat[i] = invfat[i - 1] * inv[i] % MOD;
    }
}

typedef complex<long double> Complex;
const long double PI = acos(-1.0L);

// Computes the DFT of vector v if type = 1, or the IDFT if type = -1
// If you are calculating the product of polynomials, don't forget to set both
// vectors' degrees to at least the sum of degrees of both polynomials, regardless
// of whether you will use only the first few elements of the resulting array
vector<Complex> FFT(vector<Complex> v, int type) {
    int n = v.size();
    while(n&(n-1)) { v.push_back(0); n++; }
    int logn = __builtin_ctz(n);
    vector<Complex> v2(n);
    for(int i=0; i<n; i++) {
        int mask = 0;
        for(int j=0; j<logn; j++) if(i&(1<<j)) mask |= (1<<(logn - 1 - j));
        v2[mask] = v[i];
    }
    for(int s=0, m=2; s<logn; s++, m<<=1) {
        Complex wm(cos(2.L * type * PI / m), sin(2.L * type * PI / m));        
        for(int k=0; k<n; k+=m) {
            Complex w = 1;
            for(int j=0; 2*j<m; j++) {
                Complex t = w * v2[k + j + (m>>1)], u = v2[k + j];
                v2[k + j] = u + t; v2[k + j + (m>>1)] = u - t;
                w *= wm;
            }
        }
    }
    if(type == -1) for(Complex &c: v2) c /= n;
    return v2;
}

lint go(int c, int n, int a, int b) {
    vector<Complex> pa1(2*n + 1), pa2(2*n + 1), pb(2*n + 1);
    pa1[0] = 1 / MODRT; pa2[0] = 1 % MODRT;
    pb[0] = 1;
    lint lasta = 1, lastb = 1;
    for (int i = 1; i <= n; i++) {
        lasta = lasta * a * inv[i] % MOD;
        lastb = lastb * b * inv[i] % MOD;
        pa1[i] = Complex(lasta / MODRT);
        pa2[i] = Complex(lasta % MODRT);
        pb[i] = Complex(lastb);
    }
    vector<Complex> va1 = FFT(pa1, 1);
    vector<Complex> va2 = FFT(pa2, 1);
    vector<Complex> vb = FFT(pb, 1);
    int nn = va1.size();
    for (int i = 0; i < nn; i++) {
        va1[i] = (va1[i] * vb[i]);
        va2[i] = (va2[i] * vb[i]);
    }
    va1 = FFT(va1, -1);
    va2 = FFT(va2, -1);
    vector<lint> p1, p2;
    for (Complex &x: va1) {
        p1.push_back(lint(round(x.real())) % MOD);
    }
    for (Complex &x: va2) {
        p2.push_back(lint(round(x.real())) % MOD);
    }
    lint fat = 1;
    lint ret = (p1[0]*MODRT + p2[0]) % MOD;
    for (int i = 1; i <= 2*n; i++) {
        fat = (fat * i) % MOD;
        ret = (ret + p1[i] * MODRT % MOD * fat)%MOD;
        ret = (ret + p2[i] * fat)%MOD;
    }
    return ret * c % MOD;
}    

int main() {
    int n, a, b, c;
    precalc();
    while (scanf("%d%d%d%d", &n, &a, &b, &c) > 0) {
        // debug("new test case\n");
        for (int i = 1; i <= n; i++) scanf("%d", &l[i]);
        for (int i = 1; i <= n; i++) scanf("%d", &t[i]);
        lint ans = 0;
        lint bn = 1, an = 1;
        for (int i = 1; i < n; i++) {
            bn = (bn * b)%MOD;
            an = (an * a)%MOD;
        }
        lint binom = 1, pa = 1, pb = 1;
        for (int i = 1; i < n; i++) {
            ans += (t[n - i + 1] * binom * bn) % MOD * pa % MOD;
            ans += (l[n - i + 1] * binom * an) % MOD * pb % MOD;
            binom = (binom * (n + i - 2) * inv[i]) % MOD;
            pa = (pa * a) % MOD;
            pb = (pb * b) % MOD;
        }
        ans = (ans + go(c, n - 2, a, b)) % MOD;
        printf("%lld\n", ans);
    }        
    return 0;
}
