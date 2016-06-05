#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;

int s1[MAXN], s2[MAXN];
int dp[MAXN][4];
int n;

int go(int i, int k) {
    int ret = INF;
    if (i == n) return 0;
    if (dp[i][k] != INF) return dp[i][k];
    int x1 = (k & (1 << 0)) ? 1 : 0;
    int x2 = (k & (1 << 1)) ? 1 : 0;
    if ((s1[i] ^ x1) == (s2[i] ^ x2))
        ret = min(go(i + 1, 0), 2 + go(i + 1, 3));
    else
        ret = 1 + min(go(i + 1, 1), go(i + 1, 2));
    return dp[i][k] = ret;
}    

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        scanf("%d", &n);
        int x1 = 0, x2 = 0;
        for (int i = 0; i < n; i++) {
            char c;
            scanf(" %c", &c);
            s1[i] = c - '0';
            x1 ^= s1[i];
        }
        for (int i = 0; i < n; i++) {
            char c;
            scanf(" %c", &c);
            s2[i] = c - '0';
            x2 ^= s2[i];
        }
        if (x1 != x2) {
            printf("-1\n");
            continue;
        }
        memset(dp, INF, sizeof(dp));
        printf("%d\n", go(0, 0));
    }        
    return 0;
}
