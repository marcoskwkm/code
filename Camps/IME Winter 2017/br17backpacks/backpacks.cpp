#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXV = 24;

int dp[1 << MAXV][MAXV];
vector<int> w, vol;
int n, m;
int best = INF;

int go(int mask, int i) {
    if (mask == (1 << n) - 1)
        return dp[mask][i] = best = i;
    if (i == best) return INF;
    if (dp[mask][i] != -1) return dp[mask][i];
    

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        w.push_back(x);
    }
    for (int i = 0; i < m; i++) {
        int x;
        scanf("%d", &x);
        vol.push_back(x);
    }
    sort(vol.begin(), vol.end(), greater<int>());
    m = min(m, n);
    memset(dp, -1, sizeof(dp));
    printf("%d\n", go(0, 0));    
    return 0;
}
