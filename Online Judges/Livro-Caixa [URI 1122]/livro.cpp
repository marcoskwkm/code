#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXV = 30010, MAXN = 50;

int dp[MAXV];
int v[MAXN];
char ans[MAXN];
int n, f, total;

bool check(int i, int k) {
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    if ((total + f) & 1) return 0;
    int target = (total + f) >> 1;
    if (k) target -= v[i];
    if (target < 0) return 0;
    for (int j = 0; j < n; j++) {
        if (j == i) continue;
        for (int s = target; s >= v[j]; s--)
            dp[s] |= dp[s - v[j]];
    }
    return dp[target];
}

int main() {
    while (scanf("%d%d", &n, &f) && n) {
        total = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &v[i]);
            total += v[i];
        }
        bool possible = 1;
        for (int i = 0; i < n; i++) {
            int got = 0;
            if (check(i, 0)) got += 1;
            if (check(i, 1)) got += 2;
            if (!got) possible = 0;
            if (got == 1) ans[i] = '-';
            else if(got == 2) ans[i] = '+';
            else ans[i] = '?';
        }
        ans[n] = 0;
        if (!possible) printf("*\n");
        else printf("%s\n", ans);
    }        
    return 0;
}
