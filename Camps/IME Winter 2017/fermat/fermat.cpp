#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

lint modexp(int b, int e, int m) {
    if (e == 0) return 1;
    lint aux = modexp(b, e / 2, m);
    if (e & 1) return aux * aux % m * b % m;
    return aux * aux % m;
}

typedef complex<long double> Complex;
const long double PI = acos(-1.0L);

// Computes the DFT of vector v if type = 1, or the IDFT if type = -1
// If you are calculating the product of polynomials, don't forget to set both
// vectors' degrees to at least the sum of degrees of both polynomials, regardless
// of whether you will use only the first few elements of the resulting array
vector<Complex> FFT(vector<Complex> v, int type) {
    int n = v.size();
    while (n & (n - 1)) { v.push_back(0); n++; }
    int logn = __builtin_ctz(n);
    vector<Complex> v2(n);
    for (int i = 0; i < n; i++) {
        int mask = 0;
        for (int j = 0; j<logn; j++)
            if(i&(1<<j))
                mask |= (1<<(logn - 1 - j));
        v2[mask] = v[i];
    }
    for (int s = 0, m = 2; s<logn; s++, m <<= 1) {
        Complex wm(cos(2.L * type * PI / m), sin(2.L * type * PI / m));
        for (int k = 0; k < n; k += m) {
            Complex w = 1;
            for (int j = 0; 2 * j < m; j++) {
                Complex t = w * v2[k + j + (m >> 1)], u = v2[k + j];
                v2[k + j] = u + t; v2[k + j + (m >> 1)] = u - t;
                w *= wm;
            }
        }
    }
    if (type == -1) for (Complex &c: v2) c /= n;
    return v2;
}

int main() {
    map<int, int> q;
    int n, mod;
    cin >> n >> mod;
    for (int i = 1; i < mod; i++)
        q[modexp(i, n, mod)]++;

    // for (pii p: q) printf("%d %d\n", p.first, p.second);

    vector<Complex> v(2 * mod);
    for (int i = 0; i < mod; i++)
        v[i] = Complex(q[i], 0);

    vector<Complex> vv = FFT(v, 1);
    for (Complex &c: vv) c *= c;
    vector<Complex> f = FFT(vv, -1);

    // for (auto x: f) printf("%.2Lf\n", x.real());

    lint ans = 0;
    for (int i = 0; i < mod; i++) {
        lint got = 0;
        for (size_t j = i; j < f.size(); j += mod)
            got += (lint)(f[j].real() + 0.5);
        ans += got * q[i];
    }
    cout << ans << endl;    
    return 0;
}
