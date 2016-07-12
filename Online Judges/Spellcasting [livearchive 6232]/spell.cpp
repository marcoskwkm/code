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

double get_power(double p, double e, double t) {
    double a = p / e * E, b = p / e * t;
    if (t == 29) printf("%.2f %.2f\n", a, b);
    return p / e * E * exp(p / e * t);
}

double e[MAXN], p[MAXN];
vector<int> child[MAXN];
int pai[MAXN];
double opt_e[MAXN], opt_p[MAXN];

void dfs(int v) {
    opt_e[v] = e[v], opt_p[v] = p[v];
    for (int nxt: child[v]) {
        dfs(nxt);
        double got_e = e[v] + opt_e[v] / 2, got_p = p[v] + opt_p[v];
        if (opt_e[v] * got_p < got_e * opt_p[v]) {
            opt_e[v] = got_e;
            opt_p[v] = got_p;
        }
    }
}            

int main() {
    int n;
    while(scanf("%d%lf%lf", &n, &E, &P) && n) {
        for (int i = 1; i <= n; i++) child[i].clear();
        for (int i = 1; i <= n; i++) {
            scanf("%lf%lf%d", &e[i], &p[i], &pai[i]);
            if (pai[i]) child[pai[i]].push_back(i);
        }
        for (int i = 1; i <= n; i++)
            if (!pai[i])
                dfs(i);
        double best_e = 0, best_p = 1;
        for (int i = 1; i <= n; i++) {
            if (best_e * opt_p[i] < opt_e[i] * best_p) {
                best_e = opt_e[i];
                best_p = opt_p[i];
            }
        }

        printf("E = %.2f\n", E);
        printf("best_e = %.2f, best_p = %.2f\n", best_e, best_p);
        printf("%.2f\n", get_power(best_p, best_e, 29));

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
