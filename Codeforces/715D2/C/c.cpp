#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 2010;

lint dp[MAXN][MAXN];
lint v[MAXN];

lint go(int l, int r) {
    if (dp[l][r] != -1) {
        return dp[l][r];
    }
    if (l == r) {
        return dp[l][r] = 0;
    }
    return dp[l][r] = v[r] - v[l] + min(go(l, r - 1), go(l + 1, r));
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    sort(v, v + n);

    memset(dp, -1, sizeof(dp));
    cout << go(0, n - 1) << endl;
    return 0;
}
