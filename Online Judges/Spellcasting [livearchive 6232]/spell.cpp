#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 1010;

double E, P;

inline double get_power(double p, double e, double t) {
    return p / e * E * exp(p / e * t);
}

double e[MAXN], p[MAXN];
vector<int> child[MAXN];
int pai[MAXN];
double best_e, best_p;

inline void update(double &be, double &bp, double ee, double pp) {
    if (be * pp > ee * bp) {
        be = ee;
        bp = pp;
    }
};

void dfs(int v, double cur_e, double cur_p) {
    update(best_e, best_p, cur_e, cur_p);
    for (int nxt: child[v])
        dfs(nxt, cur_e + e[nxt] / 2, cur_p + p[nxt]);
}            

int main() {
    int n;
    while(scanf("%d%lf%lf", &n, &E, &P) && n) {
        for (int i = 1; i <= n; i++) child[i].clear();
        for (int i = 1; i <= n; i++) {
            scanf("%lf%lf%d", &e[i], &p[i], &pai[i]);
            if (pai[i]) child[pai[i]].push_back(i);
        }
        best_e = 1, best_p = 0;
        for (int i = 1; i <= n; i++)
            dfs(i, e[i], p[i]);

        // printf("E = %.2f\n", E);
        // printf("best_e = %.2f, best_p = %.2f\n", best_e, best_p);
        // printf("%.2f\n", get_power(best_p, best_e, 29));

        if (E >= P) {
            printf("0\n");
            continue;
        }

        lint l = -1, r = (lint)1e18;
        while (l < r) {
            lint mid = (l + r + 1) / 2;
            if (get_power(best_p, best_e, mid) < P) l = mid;
            else r = mid - 1;
        }
        
        if (get_power(best_p, best_e, l) < P) l++;
        printf("%lld\n", l);
    }        
    return 0;
}
