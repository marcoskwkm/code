#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

const double PI = acos(-1.0L);

struct Complex {
    double a, b;
    Complex(double aa = 0, double bb = 0) : a(aa), b(bb) {}
};
static Complex operator-(const Complex &x, const Complex &y) {
    return Complex(x.a - y.a, x.b - y.b);
}
static Complex operator+(const Complex &x, const Complex &y) {
    return Complex(x.a + y.a, x.b + y.b);
}
static Complex operator*(const Complex &x, const Complex &y) {
    return Complex(x.a*y.a - x.b*y.b, x.a*y.b + x.b*y.a);
}
static Complex operator/(const Complex &x, const double &k) {
    return Complex(x.a / k, x.b / k);
}
static Complex operator*=(Complex &x, const Complex &y) { return x = x * y; }
static Complex operator/=(Complex &x, const double &k) { return x = x / k; }

// Computes the DFT of vector v if type = 1, or the IDFT if type = -1
// If you are calculating the product of polynomials, don't forget to set both
// vectors' degrees to at least the sum of degrees of both polynomials, regardless
// of whether you will use only the first few elements of the resulting array
Complex foo[(1 << 23) + 10];
vector<Complex> FFT(vector<Complex> &v, int type) {
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
        const Complex wm(cos(2.L * type * PI / m), sin(2.L * type * PI / m));
        foo[0] = 1;
        for (int i = 1; 2 * i < m; i++) {
            foo[i] = foo[i - 1] * wm;
        }
        for (int k = 0; k < n; k += m) {
            for (int j = 0; 2 * j < m; j++) {
                const Complex t = foo[j] * v2[k + j + (m >> 1)];
                v2[k + j + (m >> 1)] = v2[k + j] - t; v2[k + j] = v2[k + j] + t;
            }
        }
    }
    if (type == -1) for (Complex &c: v2) c /= n;
    return v2;
}

int main() {
    string s;
    cin >> s;

    int sum = 0;
    for (char c: s) sum += c - 'a' + 1;

    int OFF = sum;
    vector<Complex> vp(2*OFF + 1), vm(2*OFF + 1);
    int acc = 0;
    vm[OFF] = 1;
    for (char c: s) {
        acc += c - 'a' + 1;
        vp[acc] = 1;
        vm[OFF - acc] = 1;
    }

    vp = FFT(vp, 1); vm = FFT(vm, 1);
    for (size_t i = 0; i < vp.size(); i++)
        vp[i] *= vm[i];
    vp = FFT(vp, -1);

    int ans = 0;
    for (int i = OFF + 1; i <= 2 * OFF; i++)
        ans += (vp[i].a > 0.5);
    cout << ans << endl;
    return 0;
}
