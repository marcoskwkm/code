#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 110;

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

    bool operator>= (const Fraction<T> &that) const {
        return num * that.den >= that.num * den;
    }

    bool operator== (const Fraction<T> &that) const {
        return num == that.num && den == that.den;
    }

    bool operator!= (const Fraction<T> &that) const {
        return !(*this == that);
    }
};

int a[MAXN], b[MAXN];

int main() {
    int n;
    scanf("%d", &n);
    vector<Fraction<int>> cand = {Fraction<int>(0), Fraction<int>(100)};

    for (int i = 0; i < n; i++) {
        scanf("%d%d", &a[i], &b[i]);
        if (a[i] == b[i]) continue;
        else {
            if (a[i] > b[i]) cand.push_back(Fraction<int>(6000 - 100*b[i], a[i] - b[i]));
            else {
                cand.push_back(Fraction<int>(6000 - 100*b[i], a[i] - b[i]));
            }
        }
    }
    int ans = 0;
    for (auto w: cand) {
        int cnt = 0;
        if (w.num < 0) continue;
        if (w.num > 100 * w.den) continue;
        for (int i = 0; i < n; i++) {
            Fraction<int> got = w*a[i] + (Fraction<int>(100) - w)*b[i];
            if (got >= Fraction<int>(6000)) cnt++;
        }                
        ans = max(ans, cnt);
    }
    
    printf("%d\n", ans);      
    return 0;
}
