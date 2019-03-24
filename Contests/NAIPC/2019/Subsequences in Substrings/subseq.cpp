#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXS = (int)1e5 + 10, MAXT = (int)1e2 + 10;

string s, t;

int dp[MAXS][MAXT];
int go(size_t i, size_t j) {
    if (dp[i][j] != -1) return dp[i][j];
    if (j == t.size()) return dp[i][j] = i;
    if (i == s.size()) return dp[i][j] = -2;
    if (s[i] == t[j]) return dp[i][j] = go(i + 1, j + 1);
    return dp[i][j] = go(i + 1, j);
}

int main() {
    cin >> s >> t;
    memset(dp, -1, sizeof(dp));
    lint ans = 0;
    for (size_t i = 0; i < s.size(); i++) {
        int pos = go(i, 0);
        if (pos == -2) break;
        ans += s.size() - pos + 1;
    }
    cout << ans << endl;        
    return 0;
}
