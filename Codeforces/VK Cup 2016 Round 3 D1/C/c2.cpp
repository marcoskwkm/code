#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)2e5 + 10, MAXK = 55;

double dp[2][MAXN];
double t[MAXN];
double E[MAXN], St[MAXN], Sinv[MAXN];

template< class C_TYPE, class Compare = less<C_TYPE> > struct ConvexHullOpt {
    struct Line {
        C_TYPE a, b; // a + bx
        double end_l, end_r;
        Line(){}
        Line(C_TYPE aa, C_TYPE bb) { a = aa; b = bb; end_l = -LINF, end_r = LINF; }
        C_TYPE get(C_TYPE x) const { return a + b*x; }
    };

    class by_slope {
    public:
        bool operator()(const Line &a, const Line &b) const {
            return Compare()(a.b, b.b);
        }
    };
        
    class by_end {
    public:
        bool operator()(const Line &a, const Line &b) const {
            return a.end_r < b.end_r;
        }
    };

    inline double cross(const Line &a, const Line &b) {
        return double(b.a - a.a) / (a.b - b.b);
    }

    set<Line, by_slope> set_slope;
    set<Line, by_end> set_end;

    void add_line(C_TYPE a, C_TYPE b) {
        Line newline(a, b);
        auto it = set_slope.lower_bound(newline);
        vector<Line> trash;
        vector< pair<Line, Line> > update;
        if (it != set_slope.end()) {
            if (cross(*it, newline) < it->end_l) return;
            auto it2 = it;
            while (it2 != set_slope.end() && cross(*it2, newline) > it2->end_r) {
                trash.push_back(*it2);
                it2++;
            }
            if (it2 != set_slope.end()) {
                double x = cross(*it2, newline);
                newline.end_r = x;
                Line tmp = *it2;
                tmp.end_l = x;
                update.push_back(make_pair(*it2, tmp));
            }
        }
        while (it != set_slope.begin()) {
            it--;
            double x = cross(*it, newline);
            if (x > it->end_l) {
                Line tmp = *it;
                newline.end_l = x;
                tmp.end_r = x;
                update.push_back(make_pair(*it, tmp));
                break;
            }
            trash.push_back(*it);
        }
        for (const Line &line: trash) {
            set_slope.erase(line);
            set_end.erase(line);
        }
        for (const auto &upd: update) {
            set_slope.erase(upd.first);
            set_end.erase(upd.first);
            set_slope.insert(upd.second);
            set_end.insert(upd.second);
        }
        set_slope.insert(newline);
        set_end.insert(newline);
    }

    C_TYPE get(C_TYPE x) {
        if (set_end.empty()) {
            return -LINF;
        }
        Line dummy;
        dummy.end_r = x;
        auto it = set_end.lower_bound(dummy);
        return it->get(x);
    }
};


int main() {
    int N, K;
    scanf("%d%d", &N, &K);
    for (int i = 1; i <= N; i++) {
        scanf("%lf", &t[i]);
        St[i] = St[i - 1] + t[i];
        Sinv[i] = Sinv[i - 1] + 1./t[i];
        E[i] = E[i - 1] + St[i]/t[i];
    }
    for (int i = 0; i < 2; i++)
        for (int j = 0; j <= N; j++)
            dp[i][j] = LINF;
    dp[0][0] = 0;
    int cur = 1, prv = 0;
    for (int k = 1; k <= K; k++) {
        ConvexHullOpt<double> ch;
        if (k == 1) ch.add_line(0, 0);
        for (int n = 1; n <= N; n++) {
            dp[cur][n] = E[n] - ch.get(Sinv[n]);
            ch.add_line(E[n] - St[n]*Sinv[n] - dp[prv][n], St[n]);
        }
        cur ^= 1;
        prv ^= 1;
    }
    printf("%.12f\n", dp[prv][N]);    
    return 0;
}
