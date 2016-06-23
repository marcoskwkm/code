#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 1010;

template<class T> class Fraction {
    static T gcd(T a, T b) {
        while (b) {
            T na = b, nb = a % b;
            a = na, b = nb;
        }
        return a;
    }
    
public:
    T num, den;
    
    Fraction(T a = 0, T b = 1) {
        T d = gcd(a, b);
        a /= d, b /= d;
        if (b < 0) a *= -1, b *= -1;
        num = a, den = b;
    }

    Fraction<T> operator+ (const Fraction<T> &that) const {
        return Fraction(num * that.den + that.num * den, den * that.den);
    }

    Fraction<T> operator- (const Fraction<T> &that) const {
        return Fraction(num * that.den - that.num * den, den * that.den);
    }

    Fraction<T> operator* (const Fraction<T> &that) const {
        return Fraction(num * that.num, den * that.den);
    }

    Fraction<T> operator/ (const Fraction<T> &that) const {
        return Fraction(num * that.den, den * that.num);
    }

    Fraction<T> operator* (const T &that) const {
        return Fraction(num * that, den);
    }

    Fraction<T> operator/ (const T &that) const {
        return Fraction(num, that * den);
    }

    bool operator< (const Fraction<T> &that) const {
        return num * that.den < that.num * den;
    }

    bool operator> (const Fraction<T> &that) const {
        return num * that.den > that.num * den;
    }

    bool operator== (const Fraction<T> &that) const {
        return num == that.num && den == that.den;
    }

    bool operator!= (const Fraction<T> &that) const {
        return !(*this == that);
    }
};

Fraction<lint> v[MAXN];
bool seen[MAXN];
int n;
lint x[MAXN], y[MAXN], r[MAXN];

lint dist2(int i, int j) {
    return (x[i] - x[j])*(x[i] - x[j]) + (y[i] - y[j])*(y[i] - y[j]);
}

bool dfs(int i) {
    seen[i] = 1;
    for (int j = 0; j < n; j++) {
        if (i == j) continue;
        if (dist2(i, j) > (r[i] + r[j])*(r[i] + r[j])) continue;
        Fraction<lint> vj = v[i] * (-r[i]) / r[j];
        if (seen[j]) {
            if (v[j] != vj)
                return 0;
        }
        else {
            v[j] = vj;
            if (!dfs(j)) return 0;
        }
    }
    return 1;
}            

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%lld%lld%lld", &x[i], &y[i], &r[i]);
        memset(seen, 0, sizeof(seen));
        v[0] = Fraction<lint>(1, 1);
        bool ok = 1;
        if (!dfs(0)) ok = 0;
        if (!seen[n - 1]) ok = 0;
        if (!ok) printf("does not rotate\n");
        else printf("%lld/%lld %s\n", abs(v[n - 1].num), v[n - 1].den, v[n - 1] < 0 ? "counterclockwise" : "clockwise");
    }        
    return 0;
}
