#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 110;

int v[MAXN];
char ans[MAXN][MAXN];

int main() {
    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        printf("Case #%d: ", t);
        int n;
        scanf("%d", &n);
        int sum = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &v[i]);
            sum += v[i];
        }
        if (sum != n || v[0] == 0 || v[n - 1] == 0) {
            printf("IMPOSSIBLE\n");
            continue;
        }
        memset(ans, '.', sizeof(ans));
        int cur = 0;
        int best = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < v[i]; j++) {
                int x = cur, r = 0;
                while (x != i) {
                    if (x < i) ans[r++][x++] = '\\';
                    else ans[r++][x--] = '/';
                }
                best = max(best, r + 1);
                cur++;
            }
        }
        printf("%d\n", best);
        for (int r = 0; r < best; r++) {
            for (int c = 0; c < n; c++)
                printf("%c", ans[r][c]);
            printf("\n");
        }
    }        
    return 0;
}
