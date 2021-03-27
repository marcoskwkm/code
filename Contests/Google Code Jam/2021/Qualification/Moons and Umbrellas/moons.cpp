#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 1010;

string s;
int x, y;
int dp[MAXN][2];
bool seen[MAXN][2];

int go(int i, int k) {
    if (seen[i][k]) {
        return dp[i][k];
    }
    seen[i][k] = 1;
    if (i == (int)s.size()) {
        return dp[i][k] = 0;
    }
    dp[i][k] = INF;

    // use C
    if (s[i] != 'J') {
        int add = (i == 0 || k == 0) ? 0 : y;
        dp[i][k] = min(dp[i][k], go(i + 1, 0) + add);
    }

    // use J
    if (s[i] != 'C') {
        int add = (i == 0 || k == 1) ? 0 : x;
        dp[i][k] = min(dp[i][k], go(i + 1, 1) + add);
    }

    return dp[i][k];
}

int main() {
    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        cin >> x >> y >> s;
        memset(seen, 0, sizeof(seen));
        printf("Case #%d: %d\n", t, go(0, 0));
    }
    return 0;
}
