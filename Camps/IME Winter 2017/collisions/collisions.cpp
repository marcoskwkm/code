#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 20010;
const int MOD = (int)1e9 + 7;

int p[MAXN];
lint dp[MAXN][80];
int n;

lint go(int i, int take) {
    if (i == n) {
        if (take != p[i]) return 0;
        return 1;
    }
    if (dp[i][take] != -1) return dp[i][take];
    lint ret = 0;
    for (int c = 32; c <= 126; c++) {
        if ((c + take) % 31 == p[i]) {
            ret += go(i + 1, (c + take) / 31);
        }
    }
    return dp[i][take] = ret % MOD;
}

int main() {
    string s;
    getline(cin, s);
    reverse(s.begin(), s.end());
    n = s.size();
    for (int i = 0; i < n; i++) {
        int c = s[i];
        p[i] += c;
        p[i + 1] += p[i] / 31;
        p[i] %= 31;
    }
    memset(dp, -1, sizeof(dp));
    cout << go(0, 0) << endl;
    return 0;
}
