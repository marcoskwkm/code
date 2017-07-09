#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)5e4 + 10, ROOT = 250;

int v[MAXN];
lint precalc[ROOT][MAXN];
int n;
int cnt[MAXN];

int t;
int cnt_q[MAXN], last[MAXN];

lint solve_small(int il, int ir, int jl, int jr) {
    t++;
    for (int i = il; i <= ir; i++) {
        if (last[v[i]] != t) cnt_q[v[i]] = 0;            
        cnt_q[v[i]]++;
        last[v[i]] = t;
    }
    lint ret = 0;
    for (int j = jl; j <= jr; j++)
        if (last[v[j]] == t)
            ret += cnt_q[v[j]];
    return ret;
}

lint solve_large(int i, int j) {
    int ri = i / ROOT, rj = j / ROOT;
    return precalc[ri][j] + precalc[rj][i] - precalc[ri][rj * ROOT] +
        solve_small(ri * ROOT + 1, i, rj * ROOT + 1, j);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &v[i]);
    for (int r = 1; r * ROOT <= n; r++) {
        for (int i = 0; i < ROOT; i++)
            cnt[v[r * ROOT - i]]++;
        for (int i = 1; i <= n; i++)
            precalc[r][i] = precalc[r][i - 1] + cnt[v[i]];
    }
    int q;
    for (scanf("%d", &q); q--;) {
        int il, ir, jl, jr;
        scanf("%d%d%d%d", &il, &ir, &jl, &jr);
        printf("%lld\n", solve_large(ir, jr) - solve_large(il - 1, jr) -
               solve_large(ir, jl - 1) + solve_large(il - 1, jl - 1));
    }    
    return 0;
}
