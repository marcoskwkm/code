#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 3010;

int dp[MAXN][MAXN];
int v[MAXN];
lint acc[MAXN];
int accdp[MAXN][MAXN];
int n;

int main() {
    while(scanf("%d", &n) > 0) {
        for (int i = 2; i <= n + 1; i++) {
            scanf("%d", &v[i]);
            acc[i] = v[i] + acc[i - 1];
        }
        for (int i = 0; i <= n + 2; i++) {
            dp[i][n + 2] = 0;
            accdp[i][n + 2] = 0;
        }
        for (int i = n + 1; i >= 2; i--) {
            for (int last = 1; last < i; last++) {
                lint needs = acc[i - 1] - acc[last - 1];
                int l = i, r = n + 1;
                while (l < r) {
                    int mid = (l + r) / 2;
                    if (acc[mid] - acc[i - 1] >= needs) r = mid;
                    else l = mid + 1;
                }
                if (acc[l] - acc[i - 1] >= needs)
                    dp[last][i] = accdp[i][l + 1] + 1;
                else
                    dp[last][i] = 0;
                 accdp[last][i] = max(accdp[last][i + 1], dp[last][i]);
            }
        }
        printf("%d\n", dp[1][2]);        
    }            
    return 0;
}
