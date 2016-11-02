#include <bits/stdc++.h>
using namespace std;

typedef long long lint;
typedef pair<int ,int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const int MAXN = 110;

int dp[MAXN][MAXN][2];
int v[MAXN];

int go(int l, int r, int p) {
    if (l == r) return 1;
    if (dp[l][r][p] != -1) return dp[l][r][p];
    if (p == 1 && go(l, r, 0) == 0) return dp[l][r][p] = 1;

    bool seen_one = 0;
    dp[l][r][p] = 0;
    for (int take = l; take <= r; take++) {
	bool ok = 1;
	if (v[take] == 1) seen_one = 1;
	if (take > l && v[take - 1] > v[take]) ok = 0;
	if (take < r && v[take + 1] > v[take]) ok = 0;
	if (!ok) continue;
	if (seen_one) {
	    int pp = (r - take) % 2;
	    if (go(l, take - 1, pp ^ p) == 0)
		return dp[l][r][p] = 1;
	}
	else {
	    int pp = (take - l) % 2;
	    if (go(take + 1, r, pp ^ p) == 0)
		return dp[l][r][p] = 1;
	}
    }
    return dp[l][r][p] = 0;
}	

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	    scanf("%d", &v[i]);
	memset(dp, -1, sizeof(dp));
	printf("%s\n", go(0, n - 1, 0) ? "Alice" : "Bob");
    }
    return 0;
}
   
