#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 510;
const int MAXV = MAXN * MAXN;

bool dp[MAXV];
vector<int> v[2];

int solve(int i) {
    if (v[i].size() == 0) return 0;
    int total = 0;
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    for (int x: v[i]) {
        total += x;
        for (int j = total; j - x >= 0; j--)
            dp[j] |= dp[j - x];
    }
    int ans = INF;
    for (int j = 0; j <= total; j++)
        if (dp[j])
            ans = min(ans, abs(2*j - total));
    return ans;
}

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        int n;
        scanf("%d", &n);
        v[0].clear(); v[1].clear();
        for (int i = 0; i <= n; i++) {
            int x;
            scanf("%d", &x);
            v[i & 1].push_back(x);
            if (i < n) scanf(" %*c");
        }
        if (v[0].size() == 1 || v[1].size() == 1) printf("NO\n");
        else  printf("%d\n", solve(0) + solve(1));
    }
    return 0;
}
