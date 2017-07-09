#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

struct BigDouble {
    double val;
    long long exp;

    BigDouble() {}

    BigDouble(double v) : val(v), exp(0) {
        while (fabs(val) >= 10) {
            val /= 10;
            exp++;
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
        if (exp - that.exp > 10) return *this;
        if (that.exp - exp > 10) return that;
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
        if (exp - that.exp > 10) return *this;
        if (that.exp - exp > 10) return that;
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

    double to_double() {
        long double ret = val;
        for (int i = 0; i < exp; i++) ret *= 10;
        for (int i = 0; i > exp; i--) ret /= 10;
        return ret;
    }
};

const int MAXN = (int)2e6 + 10;

BigDouble factorial[MAXN];

BigDouble arrange(int n, int k) {
    if (n < 0 || k > n) return BigDouble(0);
    return factorial[n] / factorial[n - k];
}

int main() {
    factorial[0] = BigDouble(1);
    for (int i = 1; i < MAXN; i++)
        factorial[i] = BigDouble(i) * factorial[i - 1];
    
    int k, r;
    scanf("%d%d", &k, &r);
    if (r == (1 << k)) {
        printf("%.5f\n", k);
        return 0;
    }
    r = (1 << k) - r;
    BigDouble ans(0);
    for (int n_wins = 1; n_wins <= k; n_wins++) {
        if (r < (1 << n_wins) - 1) break;
        BigDouble cur_tree = BigDouble(1 << n_wins) *
            arrange(r, (1 << n_wins) - 1);
        BigDouble sibling_total = arrange((1 << k) - (1 << n_wins),
                                          (1 << n_wins));
        BigDouble sibling_subt = arrange(r - (1 << n_wins) + 1,
                                         (1 << n_wins));
        BigDouble add = cur_tree * (sibling_total - sibling_subt);
        add = add * BigDouble(1 << (k - n_wins));
        add = add * arrange((1 << k) - (1 << (n_wins + 1)),
                            (1 << k) - (1 << (n_wins + 1)));
        add = add / arrange(1 << k, 1 << k);
        ans = ans + BigDouble(n_wins) * add;
    }

    printf("%.5f\n", ans.to_double());
    return 0;
}
