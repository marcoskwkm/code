#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

long double p[32][32][2];
long double ps, pr;

long double pwin(int b, int t, int s) {
    if (p[b][t][s] == p[b][t][s]) return p[b][t][s];
    if (b == 30 || (b >= 21 && b - t > 1)) return p[b][t][s] = 1;
    if (t == 30 || (t >= 21 && t - b > 1)) return p[b][t][s] = 0;
    if (s == 0) return p[b][t][s] = pr * pwin(b + 1, t, 1) + (1 - pr) * pwin(b, t + 1, 0);
    else return p[b][t][s] = ps * pwin(b + 1, t, 1) + (1 - ps) * pwin(b, t + 1, 0);
}    

int main() {
    int s, r;
    cin >> s >> r;
    ps = (long double)(s) / 1000000000;
    pr = (long double)(r) / 1000000000;

    memset(p, -1, sizeof(p));
    long double ans = 0;
    ans += pwin(0, 0, 1) * (pwin(0, 0, 1) + (1 - pwin(0, 0, 1)) * pwin(0, 0, 0));
    ans += (1 - pwin(0, 0, 1)) * pwin(0, 0, 0) * pwin(0, 0, 1);

    printf("%.12Lf\n", ans);    
    return 0;
}
