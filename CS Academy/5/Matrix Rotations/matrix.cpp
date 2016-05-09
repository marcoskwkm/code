#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 110;

int ans[MAXN][MAXN];

int main() {
    int n;
    scanf("%d", &n);
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            int x;
            scanf("%d", &x);
            if (x) {
                ans[r][c] = ans[c][n - 1 - r] = ans[n - 1 - r][n - 1 - c] = ans[n - 1 - c][r] = 1;
            }
        }
    }
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++)
            printf("%d ", ans[r][c]);
        printf("\n");
    }    
    return 0;
}
