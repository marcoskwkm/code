#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;
const int MAXV = (int)1e6 + 10;

int hi[2][MAXV];

int main() {
    int n;
    scanf("%d", &n);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        hi[0][x] = max(hi[0][x], hi[0][x - 1] + 1);
        hi[1][x] = max(hi[1][x], hi[1][x - 1] + 1);
        if (x > 1) hi[1][x] = max(hi[1][x], hi[0][x - 2] + 2);
        ans = max(ans, max(hi[0][x] + 1, hi[1][x]));
    }
    printf("%d\n", ans);
    return 0;
}
