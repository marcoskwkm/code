#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 50, MAXM = 10010;

struct BigDouble {
    long double val;
    long long exp;

    BigDouble() {}

    BigDouble(long double v) : val(v), exp(0) {
        while (val >= 10) {
            val /= 10;
            exp++;
        }
        while (val > 0 && val < 1) {
            val *= 10;
            exp--;
        }
    }

    BigDouble operator*(const BigDouble &that) {
        BigDouble ret(val * that.val);
        ret.exp += exp + that.exp;
        return ret;
    }

    BigDouble operator/(const BigDouble &that) {
        BigDouble ret(val / that.val);
        ret.exp += exp - that.exp;
        return ret;
    }

    BigDouble operator+(BigDouble that) {
        // if (exp - that.exp > 10) return *this;
        // if (that.exp - exp > 10) return that;
        while (that.exp < exp) {
            that.val /= 10;
            that.exp++;
        }
        while (that.exp > exp) {
            that.val *= 10;
            that.exp--;
        }
        BigDouble ret(val + that.val);
        ret.exp += exp;
        return ret;
    }

    BigDouble operator-(BigDouble that) {
        // if (exp - that.exp > 10) return *this;
        // if (that.exp - exp > 10) return that;
        while (that.exp < exp) {
            that.val /= 10;
            that.exp++;
        }
        while (that.exp > exp) {
            that.val *= 10;
            that.exp--;
        }
        BigDouble ret(val - that.val);
        ret.exp += exp;
        return ret;
    }

    long double to_double() {
        long double ret = val;
        for (int i = 0; i < exp; i++) ret *= 10;
        for (int i = 0; i > exp; i--) ret /= 10;
        return ret;
    }
};

BigDouble fact[MAXM];

BigDouble arrange(int n, int k) {
    if (n < 0 || k > n) return BigDouble(0);
    return fact[n] / fact[n - k];
}

int col[MAXN];
BigDouble P[MAXM];

int main() {
    int t;
    fact[0] = BigDouble(1);
    for (int i = 1; i < MAXM; i++)
        fact[i] = BigDouble(i) * fact[i - 1];
    
    for (scanf("%d", &t); t--;) {
        int n, a, b, m;
        scanf("%d%d%d%d", &n, &a, &b, &m);
        int q = 0;
        BigDouble n_perm(1);
        for (int i = 0; i < n; i++) {
            scanf("%d", &col[i]);
            q += col[i];
            n_perm = n_perm / fact[col[i]];
        }

        n_perm = n_perm * fact[q];

        BigDouble sumP = 0;        
        for (int i = 0; i <= m; i++)
            P[i] = BigDouble(0);
        for (int mm = n; mm <= m; mm++) {
            // debug("Testing mm = %d\n", mm);
            // P[mm] = n_perm * arrange(mm, n);
            P[mm] = n_perm;
            for (int i = 0; i < n; i++)
                P[mm] = P[mm] * BigDouble(mm - i);
            for (int i = 0; i < q; i++) {
                P[mm] = P[mm] / BigDouble(mm);
            }
            sumP = sumP + P[mm];
            // if (a <= mm && mm <= b)
            //     debug("P[mm] = %.13Le, sumP = %.13Le\n", P[mm].to_double(), sumP.to_double());
        }

        
        BigDouble ans = 0;
        for (int mm = a; mm <= b; mm++)
            ans = ans + P[mm];
        // debug("ans = %.13Le\n", ans.to_double());
        ans = ans / sumP;

        printf("%.13Le\n", ans.to_double());
        // printf("%.13Lf\n", ans.to_double());        
    }        
    return 0;
}
