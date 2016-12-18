#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;

template<class C_TYPE> struct ConvexHullOpt {
    struct Line {
        C_TYPE a, b; // a + bx
        double end_l;
        C_TYPE get(C_TYPE x) { return a + b*x; }
        Line(){}
        Line(C_TYPE aa, C_TYPE bb) { a = aa; b = bb; end_l = -1e80; }
    };

    vector<Line> deq;
    int deq_l;

    double cross(const Line &r, const Line &s) {
        return double(s.a - r.a) / (r.b - s.b);
    }

    ConvexHullOpt() { clear(); }

    void add_line(C_TYPE a, C_TYPE b) {
        Line newline(a, b);
        while (deq_l < (int)deq.size() &&
               cross(newline, deq.back()) < deq.back().end_l)
            deq.pop_back();
        if (deq_l < (int)deq.size()) newline.end_l = cross(newline, deq.back());
        deq.push_back(newline);
    }

    C_TYPE get(C_TYPE x) {
        if (deq_l >= (int)deq.size()) {
            // can't query with no lines in structure =P
            abort();
        }
        while (deq_l + 1 < (int)deq.size() && deq[deq_l + 1].end_l <= x)
            deq_l++;
        return deq[deq_l].get(x);
    }

    void clear() {
        deq.clear();
        deq_l = 0;
    }
};

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        ConvexHullOpt<lint> hull;
        hull.add_line(0, 0);
        int n;
        scanf("%d", &n);
        lint ans = 0;
        for (int i = 0; i < n; i++) {
            lint x, c;
            scanf("%lld%lld", &x, &c);
            ans = hull.get(x) - c;
            if (x > 0) hull.add_line(ans - x * x, x);
        }
        if (ans > 0) printf("Ganha %lld\n", ans);
        else printf("Perde %lld\n", -ans);
    }    
    return 0;
}
