#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MOD = (int)1e9 + 7;
const int MAXN = 1010;

char grid[3][MAXN];

int main() {
    int t = 1, T;
    for (scanf("%d", &T); t <= T; t++) {
        printf("Case #%d: ", t);
        int n;
        scanf("%d", &n);
        lint ans = 1;
        for (int r = 0; r < 3; r++)
            scanf(" %s", grid[r]);
        if (n % 2 == 1 || grid[0][0] == '#' || grid[2][n - 1] == '#' || count(grid[1], grid[1] + n, '#') > 0)
            ans = 0;
        for (int c = 1; c < n - 1; c += 2) {
            int f = 0;
            if (grid[0][c] == '.' && grid[0][c + 1] == '.') f++;
            if (grid[2][c] == '.' && grid[2][c + 1] == '.') f++;
            ans = ans * f % MOD;
        }
        printf("%lld\n", ans);
    }        
    return 0;
}
