#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

struct Polynomial {
    vector<lint> coef;
    
    Polynomial(const vector<lint> &c) : coef(c) { reduce(); }

    void reduce() {
        while (coef.size() > 1 && coef.back() == 0)
            coef.pop_back();
    }
    
    Polynomial operator-(const Polynomial &q) {
        Polynomial p(coef);
        while (p.coef.size() < q.coef.size()) p.coef.push_back(0);
        for (size_t i = 0; i < q.coef.size(); i++)
            p.coef[i] -= q.coef[i];
        p.reduce();
        return p;
    }
    
    Polynomial operator*(const Polynomial &q) {
        vector<lint> prod(coef.size() + q.coef.size());
        for (size_t i = 0; i < coef.size(); i++)
            for (size_t j = 0; j < q.coef.size(); j++)
                prod[i + j] += coef[i] * q.coef[j];
        return Polynomial(prod);
    }

    Polynomial derivative() {
        vector<lint> vd(coef.size() - 1);
        for (int i = 0; i < (int)coef.size() - 1; i++)
            vd[i] = coef[i + 1] * (i + 1);
        return Polynomial(vd);
    }

    string to_string() {
        string ret = ::to_string(coef.back()) + "x^" + ::to_string(coef.size() - 1);
        for (int i = (int)coef.size() - 2; i >= 0; i--)
            ret += " + " + ::to_string(coef[i]) + "x^" + ::to_string(i);
        return ret;
    }        
};

Polynomial ONE = Polynomial({1});

Polynomial solve() {
    char c;
    scanf(" %c", &c);
    if (c == 'x') return Polynomial({0, 1});
    else {
        Polynomial p = solve();
        Polynomial q = solve();
        if (c == 'm') return ONE - (ONE - p) * (ONE - q);
        else return p * q;
    }
}

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        Polynomial F = solve().derivative();
        long double ans = 0;
        for (int i = 0; i < (int)F.coef.size(); i++)
            ans += (long double)F.coef[i] / (i + 2);
    
        printf("%.12Lf\n", ans);
    }
    return 0;
}
