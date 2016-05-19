#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 510;

pii idx_1d[MAXN];
int grid[MAXN][MAXN], reduced[MAXN][MAXN];;
int l_idx[MAXN], r_idx[MAXN];
pii st[MAXN];

lint solve1D(int row, int a, int b, int n, int m) {
    int siz = 0;
    st[siz++] = pii(-INF, -1);
    for (int i = 0; i < m; i++) {
        while (st[siz - 1].first >= reduced[row][i]) siz--;
        l_idx[i] = st[siz - 1].second;
        st[siz++] = pii(reduced[row][i], i);
    }
    siz = 0;
    st[siz++] = pii(-INF, m);
    for (int i = m - 1; i >= 0; i--) {
        while (st[siz - 1].first >= reduced[row][i]) siz--;
        r_idx[i] = st[siz - 1].second;
        st[siz++] = pii(reduced[row][i], i);
    }
        
    lint ans = 0;
    for (int i = 0; i < m; i++) {
        lint h0 = reduced[row][i];
        int l = l_idx[i], r = r_idx[i];
        int len = min(b, r - l - 1);
        lint num = h0 * m * lint(n);
        int den = n * m - a * len;
        lint h = num / den;
        if (num % den == 0) h--;
        ans = max(ans, a * len * h);
    }
    return ans;
}        
        
int main() {
    int a, b, n, m;
    scanf("%d%d%d%d", &a, &b, &n, &m);
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            scanf("%d", &grid[r][c]);
            reduced[r][c] = grid[r][c];
        }
    }

    int hi = max(a, b), lo = min(a, b);
    lint ans = 0;
    for (int aa = 1; aa <= hi; aa++) {
        int bb = (aa <= lo ? hi : lo);
        for (int r = 0; r + aa - 1 < n; r++) {
            for (int c = 0; c < m; c++)
                reduced[r][c] = min(reduced[r][c], grid[r + aa - 1][c]);
            ans = max(ans, solve1D(r, aa, bb, n, m));
        }
    }
    printf("%lld\n", ans);    
    return 0;
}
